//=============================================================================
//
// 弾
// Author : 村元翼
//
//=============================================================================
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "scene.h"
#include "keyboard.h"
#include "effect.h"
#include "collision.h"
#include "enemy.h"
#include "player.h"
#include "game.h"
#include "score.h"
#include "MiniPolygon.h"
#include "game.h"

//=============================================================================
// 静的メンバ変数の初期化
//=============================================================================
int CBullet::m_nAll = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
CBullet::CBullet(OBJTYPE nPriority) : CScene2D(nPriority)
{
	// メンバ変数の初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLifeSpan = 0;
	m_fSpeed = 0;
	m_bUse = false;

	// 弾数のカウント
	m_nAll++;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBullet::~CBullet()
{
	if (m_pEffect != nullptr)
	{
		m_pEffect->Uninit();
		delete m_pEffect;
		m_pEffect = nullptr;
	}

	if (m_pMiniBullet != nullptr)
	{
		m_pMiniBullet->Uninit();
		delete m_pMiniBullet;
		m_pMiniBullet = nullptr;
	}

	m_nAll--;
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CBullet::Init(void)
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
void CBullet::Uninit(void)
{
	m_bUse = false;
	CScene2D::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CBullet::Update(void)
{
	if (m_bUse == true)
	{
		CScene2D::Update();							// 2Dポリゴン更新
		CScene2D::SetPos(m_pos, m_scale);			// 位置の更新
		m_pos = CScene::GetPos();					// 位置の取得

		m_pMiniBullet->Move(-m_move);

		// 画面外に行く
		if (m_pos.x <= (-CGame::GetScrollPos().x / 2) ||
			m_pos.x >= (SCREEN_WIDTH * 2) - (CGame::GetScrollPos().x / 2) ||
			m_pos.y <= (-CGame::GetScrollPos().y / 2) ||
			m_pos.y >= (SCREEN_HEIGHT * 2) - (CGame::GetScrollPos().y / 2))
		{
			Uninit();
		}

		// 弾の寿命判定
		if (m_nLifeSpan <= 0)
		{
			Uninit();
		}

		else
		{
			m_nLifeSpan--;												// 弾の寿命を減らす
			m_move = CScene2D::Move(&m_pos, m_fAngle, m_fSpeed);		// 弾の移動
		}

		//----------------------------------------------------------------------
		// 敵との当たり判定
		//----------------------------------------------------------------------
		CCollision *pCollision = new CCollision;
		CScene *pScene = CScene::GetScene(CScene::OBJTYPE_ENEMY);

		while (pScene != nullptr)
		{
			CScene *pSceneNext = CScene::GetSceneNext(pScene);

			if (pScene != nullptr)
			{
				// 円と四角の当たり判定
				if (pCollision->CircleCollision(this, pScene) == true)
				{
					CEffect::Create(
						m_pos,
						D3DXVECTOR3(m_fSpeed, m_fSpeed, 0.0f),
						D3DXVECTOR3(150.0f,150.0f,0.0f),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						0.0f, 0.0f, 0.0f,
						CEffect::EFFECT_EXPLOSION,
						CTexture::Explosion);		// 爆発エフェクト生成

					CScore *pScore;
					pScore = CGame::GetScore();		// スコア取得
					pScore->AddScore(100);			// スコア加算
					Uninit();						// 弾の消滅
					pScene->Uninit();				// 敵の消滅
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
}

//=============================================================================
// 描画
//=============================================================================
void CBullet::Draw(void)
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
// 弾の生成
//=============================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,float angle, CTexture::Type texture)
{
	// インスタンス生成
	CBullet *pBullet = new CBullet(OBJTYPE_BULLET);

	// プレイヤー情報の取得
	pBullet->m_pos = pos;							// 位置
	pBullet->m_scale = scale;						// 大きさ
	pBullet->m_fAngle = angle;						// 角度
	pBullet->m_Tex = texture;						// テクスチャ
	pBullet->m_nLifeSpan = 60;						// ライフ
	pBullet->m_fSpeed = 15.0f;						// 速度
	pBullet->m_bUse = true;							// 弾の使用状況

	if (pBullet != nullptr)
	{
		pBullet->Init();	// 初期化処理

	// エフェクトの生成
		pBullet->m_pEffect = CEffect::Create
		(
			pBullet->m_pos,												// 位置
			D3DXVECTOR3(pBullet->m_fSpeed, pBullet->m_fSpeed, 0.0f),	// 速度
			D3DXVECTOR3(60.0f, 60.0f, 0.0f),							// 大きさ
			D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f),							// カラー
			0.1f,														// 縮小速度
			0.01f,														// 透明化速度
			pBullet->m_fAngle,											// 角度
			CEffect::EFFECT_BULLET,										// エフェクトタイプ
			CTexture::Effect											// テクスチャタイプ
		);

		// ミニマップの弾の生成
		pBullet->m_pMiniBullet = CMiniPolygon::Create
		(
			D3DXVECTOR3							// 位置
			(
				pBullet->GetPos().x,
				pBullet->GetPos().y,
				0.0f
			),
			D3DXVECTOR3							// サイズ
			(
				pBullet->GetScale().x,
				pBullet->GetScale().y,
				0.0f
			),
			CMiniPolygon::MINIPOLYGON_BULLET	// ミニマップのポリゴンのタイプ
		);
	}

	return pBullet;
}
