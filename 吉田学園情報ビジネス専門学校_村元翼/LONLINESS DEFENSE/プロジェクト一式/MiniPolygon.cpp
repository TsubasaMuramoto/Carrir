//=============================================================================
//
// MiniPolygon処理
// Author : 村元翼
//
//=============================================================================
#include "MiniPolygon.h"
#include "polygon.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "enemy.h"
#include "game.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CMiniPolygon::CMiniPolygon(OBJTYPE nPriority) : CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUse = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMiniPolygon::~CMiniPolygon()
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CMiniPolygon::Init(void)
{
	// CScene2D::BindTexture(m_Tex);
	CScene2D::Init();
	CScene2D::SetPos(m_pos, m_scale);
	CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CMiniPolygon::Uninit(void)
{
	m_bUse = false;
	CScene2D::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CMiniPolygon::Update(void)
{
	if (m_bUse)
	{
		CScene2D::Update();

		// タイプ別更新処理
		switch (m_type)
		{
		case MINIPOLYGON_PLAYER:
			Move(CScene::GetScene(OBJTYPE_PLAYER)->GetMove());
			SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			break;

		case MINIPOLYGON_ENEMY:
			SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;

		case MINIPOLYGON_TARGET:
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		}
	}
}

//=============================================================================
// 描画
//=============================================================================
void CMiniPolygon::Draw(void)
{
	// デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// アルファブレンド
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);

	CScene2D::Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
}

//=============================================================================
// ミニポリゴンの生成
//=============================================================================
CMiniPolygon *CMiniPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, MINIPOLYGON_TYPE type)
{
	//インスタンス生成
	CMiniPolygon *pMiniPolygon = new CMiniPolygon(OBJTYPE_POLYGON);

	if (pMiniPolygon != nullptr)
	{
		//						↓ミニマップの右上を始点に		↓スクロールした分の位置を2で割りposに足し、位置をミニポリゴンの大きさで割る
		pMiniPolygon->m_pos = CPolygon::GetVtx1() + ((pos +(CGame::GetScrollPos() / 2)) / DIVISION_SIZE);
		pMiniPolygon->m_scale = scale / DIVISION_SIZE;
		pMiniPolygon->m_type = type;
		pMiniPolygon->m_bUse = true;
		
		// タイプ別初期化処理
		switch (pMiniPolygon->m_type)
		{
		case MINIPOLYGON_PLAYER:
			break;

		case MINIPOLYGON_ENEMY:
			
			break;

		case MINIPOLYGON_TARGET:
			pMiniPolygon->BindTexture(CTexture::Target);
			break;
		}

		// 初期化処理
		pMiniPolygon->Init();
	}

	return pMiniPolygon;
}

//=============================================================================
// 移動
//=============================================================================
void CMiniPolygon::Move(D3DXVECTOR3 speed)
{
	// 移動量が0以外の時
	if (speed.x != 0.0f || speed.y != 0.0f)
	{
		// 座標更新
		if (speed.x != 0.0f)
		{
			m_pos.x += (speed.x / DIVISION_SIZE);
		}
		if (speed.y != 0.0f)
		{
			m_pos.y += (speed.y / DIVISION_SIZE);
		}

		CScene2D::SetPos(m_pos, m_scale, false);
	}
}