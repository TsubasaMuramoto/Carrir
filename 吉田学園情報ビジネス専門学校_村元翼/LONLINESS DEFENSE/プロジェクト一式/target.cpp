//=============================================================================
// 弾
// Author : 村元翼
//=============================================================================
#include "target.h"
#include "collision.h"
#include "manager.h"
#include "renderer.h"
#include "effect.h"
#include "gauge.h"
#include "MiniPolygon.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTarget::CTarget(OBJTYPE nPriority) : CScene2D(nPriority)
{
	// メンバ変数の初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_nInvincibleTime = 0;
	m_bUse = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTarget::~CTarget()
{
	// オブジェクト終了
	if (m_pMiniTarget != nullptr)
	{
		m_pMiniTarget->Uninit();
		m_pMiniTarget = nullptr;
	}
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CTarget::Init(void)
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
void CTarget::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CTarget::Update(void)
{
	CScene2D::Update();							// 2Dポリゴン更新
	CScene2D::SetPos(m_pos, m_scale);			// 位置の更新
	m_pos = CScene::GetPos();					// 位置の取得

	//=============================================================
	// 敵との当たり判定
	//=============================================================
	CCollision *pCollision = new CCollision;
	CScene *pScene = CScene::GetScene(CScene::OBJTYPE_ENEMY);

	while (pScene != nullptr)
	{
		// 現在の次のシーン
		CScene *pSceneNext = CScene::GetSceneNext(pScene);

		// 当たり判定
		if (pScene != nullptr)
		{
			if (m_nInvincibleTime <= 0)
			{
				m_nInvincibleTime = 0;
				CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// カラーを通常に戻す

				// 円の当たり判定
				if (pCollision->CircleCollision(this, pScene) == true)
				{
					if (m_nLife <= 0)	// 体力が0になった時
					{
						Uninit();
					}
					else				// そうでない時	
					{
						CEffect::Create(
							pScene->GetPos(),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXVECTOR3(150.0f, 150.0f, 0.0f),
							D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
							0.0f, 0.0f, 0.0f,
							CEffect::EFFECT_EXPLOSION,
							CTexture::Explosion);								// 爆発のエフェクト生成

						CGauge::SetGauge(DECREASE_GAUGE);						// 体力ゲージを減らす
						CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// 透明にする
						m_nLife--;												// 体力を減らす
					}

					pScene->Uninit();											// 敵の消滅
					m_nInvincibleTime = INVINCIBLE_TIME;						// 透明化タイムの初期化
				}
			}

			else
			{
				m_nInvincibleTime--;
			}
		}

		// 次のオブジェクトを見る
		pScene = pSceneNext;
	}

	if (pCollision != nullptr)
	{
		delete pCollision;
		pCollision = nullptr;
	}

}

//=============================================================================
// 描画
//=============================================================================
void CTarget::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//デバイスのポインタ

	// アルファブレンド
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);

	CScene2D::Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
}

//=============================================================================
// ターゲットの生成
//=============================================================================
CTarget *CTarget::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, CTexture::Type texture)
{
	// インスタンス生成
	CTarget *pTarget = new CTarget(OBJTYPE_TARGET);

	// プレイヤー情報の取得
	if (pTarget != NULL)
	{
		pTarget->m_pos = pos;							// 位置
		pTarget->m_scale = scale;						// 大きさ
		pTarget->m_Tex = texture;						// テクスチャ
		pTarget->m_nLife = 100;							// 体力
		pTarget->m_nInvincibleTime = 0;					// 無敵時間
		pTarget->m_bUse = true;							// 弾の使用状況
		pTarget->Init();								// 初期化処理

		pTarget->m_pMiniTarget = CMiniPolygon::Create	// ミニマップのターゲットの生成
		(
			D3DXVECTOR3							// 位置
			(
				pTarget->GetPos().x,
				pTarget->GetPos().y,
				0.0f
			),
			D3DXVECTOR3							// サイズ
			(
				pTarget->GetScale().x,
				pTarget->GetScale().y,
				0.0f
			),
			CMiniPolygon::MINIPOLYGON_TARGET	// タイプ
		);
	}

	return pTarget;
}


