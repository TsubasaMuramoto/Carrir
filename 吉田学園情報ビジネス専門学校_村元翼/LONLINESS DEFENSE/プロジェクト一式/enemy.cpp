//=============================================================================
//
// 敵処理
// Author : 村元翼
//
//=============================================================================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "keyboard.h"
#include "score.h"
#include "game.h"
#include "polygon.h"
#include "MiniPolygon.h"
#include "collision.h"
#include "effect.h"

//=============================================================================
// 静的メンバ変数の初期化
//=============================================================================
int CEnemy::m_nAll = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemy::CEnemy(OBJTYPE nPriority) : CScene2D(nPriority)
{
	// メンバ変数の初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_nFrame = 0;
	m_nPattern = 0;
	m_bUse = false;

	// 敵の数カウント
	m_nAll++;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{
	m_nAll--;
}

//------------------------------------------------------------
// 頂点座標の設定
//------------------------------------------------------------
void CEnemy::SetPos(D3DXVECTOR3 pos)
{
	CScene::SetPos(pos);

	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//バッファの生成
	pVtx[0].pos = D3DXVECTOR3(pos.x - m_scale.x, pos.y - m_scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + m_scale.x, pos.y - m_scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - m_scale.x, pos.y + m_scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + m_scale.x, pos.y + m_scale.y, 0.0f);

	m_pVtxBuff->Unlock();

}
//=============================================================================
// 初期化
//=============================================================================
HRESULT CEnemy::Init(void)
{
	CScene2D::BindTexture(m_Tex);
	CScene2D::Init();
	CScene2D::SetPos(m_pos, m_scale);
	CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CEnemy::Uninit(void)
{
	if (m_pMiniEnemy != nullptr)
	{
		m_pMiniEnemy->Uninit();
		delete m_pMiniEnemy;
		m_pMiniEnemy = nullptr;
	}

	m_bUse = false;
	CScene2D::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CEnemy::Update(void)
{
	if (m_bUse == true)
	{
		// ミニマップの敵の移動
		m_pMiniEnemy->Move(m_move);

		CScene2D::Update();
		CScene2D::SetPos(m_pos, m_scale);
		CScene2D::SetTex((float)m_nPattern, 0.0f, 0.5f, 1.0f);
		m_pos = CScene::GetPos();

		//----------------------------------------------------------------------
		// ターゲットとの当たり判定
		//----------------------------------------------------------------------
		CScene *pScene = CScene::GetScene(CScene::OBJTYPE_TARGET);
		while (pScene != NULL)
		{
			// 次のシーンを取得
			CScene *pSceneNext = CScene::GetSceneNext(pScene);

			// ターゲットに追従する処理
			FeaturedTarget(&pScene->GetPos(), &m_pos);

			// 次のシーンを現在のシーンにする
			pScene = pSceneNext;	
		}

		//----------------------------------------------------------------------
		// プレイヤーとの当たり判定
		//----------------------------------------------------------------------
		CCollision *pCollision = new CCollision;
		CScene *pScene2 = CScene::GetScene(CScene::OBJTYPE_PLAYER);
		while (pScene2 != NULL)
		{
			// 次のシーンを取得
			CScene *pSceneNext2 = CScene::GetSceneNext(pScene2);

			if (pScene2 != NULL)
			{
				// 四角と四角の当たり判定
				if (pCollision->SetCollision(this, pScene2) == true)
				{
					CEffect::Create(
						m_pos,
						m_Speed,
						D3DXVECTOR3(150.0f, 150.0f, 0.0f),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						0.0f, 0.0f, 0.0f,
						CEffect::EFFECT_EXPLOSION,
						CTexture::Explosion);			// 爆発のエフェクト生成

					CScore *pScore = CGame::GetScore();	// スコア取得
					pScore->AddScore(100);				// スコア加算
					Uninit();							// 敵の消滅
				}
			}

			// 次のオブジェクトを見る
			pScene2 = pSceneNext2;
		}

		if (pCollision != nullptr)
		{
			delete pCollision;
			pCollision = nullptr;
		}


	}

	// フレームカウント
	m_nFrame++;

	// 敵アニメーションを進める
	if (m_nFrame >= 30)
	{
		m_nFrame = 0;
		m_nPattern++;
	}

	// アニメーションを0に戻す
	if (m_nPattern >= 2)
	{
		m_nPattern = 0;
	}
}

//=============================================================================
// 描画
//=============================================================================
void CEnemy::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//デバイスのポインタ

	// アルファブレンド
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);

	CScene2D::Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
}

//=============================================================================
// 敵の生成
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, CTexture::Type texture)
{
	// インスタンス生成
	CEnemy *pEnemy = new CEnemy(OBJTYPE_ENEMY);

	if (pEnemy != nullptr)
	{
		// プレイヤー情報の取得
		pEnemy->m_pos = pos;
		pEnemy->m_scale = scale;
		pEnemy->m_Tex = texture;
		pEnemy->m_nLife = 240;
		pEnemy->m_Speed = ENEMY_SPEED;
		pEnemy->m_bUse = true;

		// 初期化処理
		pEnemy->Init();

		// ミニマップの敵の生成
		pEnemy->m_pMiniEnemy = CMiniPolygon::Create
		(
			D3DXVECTOR3						// 位置
			(
				pEnemy->GetPos().x,
				pEnemy->GetPos().y,
				0.0f
			),
			D3DXVECTOR3						// サイズ
			(
				pEnemy->GetScale().x,
				pEnemy->GetScale().y,
				0.0f
			),
			CMiniPolygon::MINIPOLYGON_ENEMY	// ミニマップのポリゴンタイプ
		);
	}

	return pEnemy;
}

//=============================================================================
// 敵の移動
//=============================================================================
void CEnemy::Move(void)
{
	// m_pos.x += m_nSpeed;
	// m_pos.y += m_nSpeed;
}

//=============================================================================
// ターゲットに対象がついていく処理
//=============================================================================
void CEnemy::FeaturedTarget(D3DXVECTOR3 *targetPos, D3DXVECTOR3 *featuredPos)
{
	// ターゲットの位置と追従するオブジェクトの位置の差分を求める
	float fLengthX = (targetPos->x - featuredPos->x);
	float fLengthY = (targetPos->y - featuredPos->y);

	// 斜めの距離を求める
	float fLengthTrue = sqrtf(fLengthX * fLengthX + fLengthY * fLengthY);

	// 正規化
	m_move.x = fLengthX / fLengthTrue;
	m_move.y = fLengthY / fLengthTrue;

	// 速度を掛ける
	m_move.x *= m_Speed.x;
	m_move.y *= m_Speed.y;

	// 座標更新
	featuredPos->x += m_move.x;
	featuredPos->y += m_move.y;

	CScene::SetMove(m_move);
}