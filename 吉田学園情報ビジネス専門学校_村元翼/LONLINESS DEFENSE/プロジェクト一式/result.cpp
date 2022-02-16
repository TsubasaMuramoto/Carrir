//--------------------------------------
//リザルト画面の処理
//--------------------------------------
#include "result.h"
#include "bg.h"
#include "texture.h"
#include "manager.h"
#include "keyboard.h"
#include "fade.h"
#include "polygon.h"
#include "ranking.h"
#include "XInput.h"
//#include "sound.h"

//--------------------------------------------
//コンストラクタ
//--------------------------------------------
CResult::CResult()
{
	m_bNextMode = false;
	m_Cursol = NULL;
	m_bNextMode = false;
}
//--------------------------------------------
//デストラクタ
//--------------------------------------------
CResult::~CResult()
{

}

//--------------------------------------------
//初期化
//--------------------------------------------
HRESULT CResult::Init(void)
{

	//ランキングの生成
	m_pRanking = CRanking::Create
	(
		D3DXVECTOR3(500.0f + RANKING_POLYGON_WIDTH * MAX_SCORE, RESULT_RANKING_POSY, 0.0f),
		D3DXVECTOR3(RANKING_POLYGON_WIDTH, RANKING_POLYGON_HEIGHT, 0.0f)
	);

	//CBg::Create(false, CTexture::Result, CScene::OBJTYPE_BG);	//背景


	//if (CManager::GetClear() == true)
	//{
	//	m_pBg = CBg::Create(CTexture::GameClear000, CScene::OBJTYPE_BG, false);	//背景
	//	pPolygon[0] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50.0f, 0.0f), D3DXVECTOR3(500.0f, 300.0f, 0.0f), CTexture::GameClear001);	//ゲームオーバー
	//}
	//else
	//{
	//	m_pBg = CBg::Create(CTexture::GameOver, CScene::OBJTYPE_BG, false);	//背景
	//	pPolygon[0] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 280.0f, 0.0f), D3DXVECTOR3(800.0f, 450.0f, 0.0f), CTexture::Gameover000);	//ゲームオーバー

	//}
	//pPolygon[1] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 80.0f, 0.0f), D3DXVECTOR3(200, 40.0f, 0.0f), CTexture::Retry);	//リトライ
	//pPolygon[2] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR3(200, 40.0f, 0.0f), CTexture::Texture001);	//タイトルに戻る
	//m_Cursol = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CTexture::Cursol);	//タイトルに戻る
	//																																						//m_pBg->SetCol(D3DXCOLOR(0.0, 0.0, 1.0, 1.0));

	return S_OK;
}
//--------------------------------------------
//終了
//--------------------------------------------
void CResult::Uninit(void)
{
	/*if (m_pBg != NULL)
	{
		m_pBg->Uninit();
		m_pBg = NULL;
	}
	for (int nCnt = 0; nCnt < MAX_RESULT; nCnt++)
	{
		if (pPolygon[nCnt] != NULL)
		{
			pPolygon[nCnt]->Uninit();
			pPolygon[nCnt] = NULL;
		}
	}
	if (m_Cursol != NULL)
	{
		m_Cursol->Uninit();
		m_Cursol = NULL;
	}*/

	if (m_pRanking != nullptr)
	{
		m_pRanking->Uninit();
		//delete m_pRanking;
		m_pRanking = nullptr;
	}
}
//--------------------------------------------
//更新
//--------------------------------------------
void CResult::Update(void)
{
	CInputkeyboard *pKey = CManager::GetKeyboard();
	CXInput *pGamePad = CManager::GetXInput();	

	// ENTERを押す
	if (pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_START) || pKey->GetTrigger(DIK_RETURN) == true && m_bNextMode == false)
	{
		CFade::SetFade(CManager::MODE_TITLE);			// ゲームモードへ
		m_bNextMode = true;								// ENTER連打防止
	}
}
//--------------------------------------------
//描画
//--------------------------------------------
void CResult::Draw(void)
{

}

