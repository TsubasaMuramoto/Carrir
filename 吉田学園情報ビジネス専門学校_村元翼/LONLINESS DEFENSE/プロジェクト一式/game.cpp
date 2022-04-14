//--------------------------------------
//ゲーム画面の処理
//--------------------------------------
#include "game.h"
#include "bg.h"
#include "texture.h"
#include "manager.h"
#include "keyboard.h"
#include "XInput.h"
#include "player.h"
#include "fade.h"
#include "time.h"
#include "enemy.h"
#include "polygon.h"
#include "pause.h"
#include "score.h"
#include "target.h"
#include "gauge.h"
#include "MiniPolygon.h"
#include "sound.h"

//---------------------------------------
// マクロ定義
//---------------------------------------
#define POP_TIMING (60)								// 出現のタイミング

//-----------------------------------------------------
// 静的メンバ変数の初期化
//-----------------------------------------------------
CScene2D		*CGame::m_pGaugeFrame	= nullptr;
CBg				*CGame::m_pBg			= nullptr;
CPlayer			*CGame::m_pPlayer		= nullptr;
CTime			*CGame::m_pTime			= nullptr;
CScore			*CGame::m_pScore		= nullptr;
CPolygon		*CGame::m_pMiniMap		= nullptr;
CTarget			*CGame::m_pTarget		= nullptr;
CGauge			*CGame::m_pGauge		= nullptr;
CMiniPolygon	*CGame::m_pMiniPlayer	= nullptr;
int				CGame::m_nSpawnTimer	= 0;
D3DXVECTOR3		CGame::m_ScrollSpeed	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3		CGame::m_ScrollPos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//--------------------------------------------
//コンストラクタ
//--------------------------------------------
CGame::CGame()
{
	m_pPlayer		= nullptr;
	m_pBg			= nullptr;
	m_pTime			= nullptr;
	m_pScore		= nullptr;
	m_pGauge		= nullptr;
	m_pMiniMap		= nullptr;
	m_pMiniPlayer	= nullptr;
	m_pTarget		= nullptr;
	m_bNextMode		= false;
	m_ScrollSpeed	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ScrollPos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//--------------------------------------------
//デストラクタ
//--------------------------------------------
CGame::~CGame()
{

}
//--------------------------------------------
//初期化
//--------------------------------------------
HRESULT CGame::Init(void)
{
	// 地球の体力ゲージ生成
	if (m_pGauge == nullptr)
	{
		m_pGaugeFrame = CScene2D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CTexture::GaugeFrame,CScene::OBJTYPE_POLYGON);
		m_pGaugeFrame->SetScalePos(D3DXVECTOR3(GAUGE_POS.x - 10.0f, GAUGE_POS.y, 0.0f), D3DXVECTOR3(MAX_GAUGE_WIDTH + 20.0f, 50.0f, 0.0f));
		m_pGauge = CGauge::Create(GAUGE_POS, D3DXVECTOR3(MAX_GAUGE_WIDTH, 40.0f, 0.0f));
	}

	// ミニマップ生成
	if (m_pMiniMap == nullptr)
	{
		m_pMiniMap = CPolygon::Create(MINIMAP_POS, MINIMAP_SIZE, CTexture::MapFrame);
	}

	// 背景生成
	if (m_pBg == nullptr)
	{
		m_pBg = CBg::Create(true);
	}

	// 地球生成
	if (m_pTarget == nullptr)
	{
		m_pTarget = CTarget::Create(TARGET_POS, TARGET_SIZE);
	}

	// プレイヤー生成
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = CPlayer::Create(PLAYER_POS, PLAYER_SIZE);
	}

	// ミニプレイヤー生成
	if (m_pMiniPlayer == nullptr)
	{
		m_pMiniPlayer = CMiniPolygon::Create
		(
			D3DXVECTOR3
			(
				m_pPlayer->GetPos().x,
				m_pPlayer->GetPos().y,
				0.0f
			),
			D3DXVECTOR3
			(
				m_pPlayer->GetScale().x,
				m_pPlayer->GetScale().y,
				0.0f
			),
			CMiniPolygon::MINIPOLYGON_PLAYER
		);
	}

	// タイム生成
	if (m_pTime == nullptr)
	{
		m_pTime = CTime::Create(TIME_POS, TIME_SIZE);
	}

	// スコア生成
	if (m_pScore == nullptr)
	{
		m_pScore = CScore::Create(SCORE_POS, SCORE_SIZE);
	}

	return S_OK;
}
//--------------------------------------------
// 終了
//--------------------------------------------
void CGame::Uninit(void)
{
	//--------------------------------
	// オブジェクトの終了
	//--------------------------------
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}

	if (m_pBg != nullptr)
	{
		m_pBg->Uninit();
		delete m_pBg;
		m_pBg = nullptr;
	}

	if (m_pGauge != nullptr)
	{
		m_pGauge->Uninit();
		delete m_pGauge;
		m_pGauge = nullptr;
	}

	if (m_pTime != nullptr)
	{
		m_pTime->Uninit();
		delete m_pTime;
		m_pTime = nullptr;
	}
	if (m_pScore != nullptr)
	{
		m_pScore->Uninit();
		delete m_pScore;
		m_pScore = nullptr;
	}
}
//--------------------------------------------
// 更新
//--------------------------------------------
void CGame::Update(void)
{
	// 入力デバイスの取得
	CInputkeyboard *pKey = CManager::GetKeyboard();
	CXInput *pGamePad = CManager::GetXInput();

	if (!CManager::GetPause())
	{
		//-------------------------------------------------------------------------
		// 敵のランダム出現処理
		//-------------------------------------------------------------------------
		m_nSpawnTimer++;

		// タイマーが敵出現タイムを超える
		if (m_nSpawnTimer >= POP_TIMING)
		{
			std::random_device seed;													// 乱数生成器でシード値を完全ランダムに初期化する
			std::mt19937_64 mtRand(seed());												// 疑似乱数を作り出す
			std::uniform_int_distribution<> Pop_Pos(1, FROM_MAX - 1);					// 出現位置を決める(上下左右の４方向)
			int nPop = Pop_Pos(mtRand);													// 乱数結果を整数に代入する

				// 上下
			if (nPop == FROM_UP || nPop == FROM_DOWN)
			{
				std::uniform_real_distribution<float> RangeX(0.0f, SCREEN_WIDTH * 2);	// 指定した範囲内の数値を等確率で返す(最小値以上、最大値"未満")

				// 上
				if (nPop == FROM_UP)
				{
					CEnemy::Create(D3DXVECTOR3(RangeX(mtRand), 0.0f, 0.0f) - (m_ScrollPos / 2), ENEMY_SIZE);
				}

				// 下
				else if (nPop == FROM_DOWN)
				{
					CEnemy::Create(D3DXVECTOR3(RangeX(mtRand), SCREEN_HEIGHT * 2, 0.0f) - (m_ScrollPos / 2), ENEMY_SIZE);
				}
			}

			// 左右
			else if (nPop == FROM_LEFT || nPop == FROM_RIGHT)
			{
				std::uniform_real_distribution<float> RangeY(0.0f, SCREEN_HEIGHT * 2);	// 指定した範囲内の数値を等確率で返す(最小値以上、最大値"未満")

				// 左
				if (nPop == FROM_LEFT)
				{
					CEnemy::Create(D3DXVECTOR3(0.0f, RangeY(mtRand), 0.0f) - (m_ScrollPos / 2), ENEMY_SIZE);
				}

				// 右
				else if (nPop == FROM_RIGHT)
				{
					CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH * 2, RangeY(mtRand), 0.0f) - (m_ScrollPos / 2), ENEMY_SIZE);
				}
			}

			// タイマーリセット
			m_nSpawnTimer = 0;
		}
	}
}
//--------------------------------------------
// 描画
//--------------------------------------------
void CGame::Draw(void)
{
}

//--------------------------------------------
// ゲーム画面のスクロールの設定
//--------------------------------------------
void CGame::SetScroll(const char* Direction, D3DXVECTOR3 speed)
{
	if (Direction == "X")
	{
		m_ScrollSpeed.x = speed.x;
	}

	if (Direction == "Y")
	{
		m_ScrollSpeed.y = speed.y;
	}

	if (Direction == "StopX")
	{
		m_ScrollSpeed.x = 0.0f;
	}

	if (Direction == "StopY")
	{
		m_ScrollSpeed.y = 0.0f;
	}

	// スクロール座標更新
	m_ScrollPos += m_ScrollSpeed;
}




