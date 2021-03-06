//----------------------------------
//ポリゴンの処理
//-----------------------------------
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "game.h"
#include "bg.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CScene2D::CScene2D(OBJTYPE nPriority) :CScene(nPriority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CScene2D::~CScene2D()
{

}

//---------------------------------------------------------------
// インスタンス生成処理
//---------------------------------------------------------------
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CTexture::Type texture,CScene::OBJTYPE objtype)
{
	// インスタンス生成
	CScene2D *pScene2D = new CScene2D(objtype);

	// ポリゴン初期化
	if (pScene2D != nullptr)
	{
		pScene2D->Init();
		pScene2D->BindTexture(texture);
		pScene2D->SetPos(pos, size);
	}
	return pScene2D;
}

//=============================================================================
// テクスチャの取得
//=============================================================================
void CScene2D::BindTexture(CTexture::Type type)
{
	m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture(type);
}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CScene2D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//デバイスのポインタ

	 // 頂点情報を設定
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL
	);

	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//バッファの生成
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2(1.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 1.0);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CScene2D::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	Release();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CScene2D::Update(void)
{

}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスのポインタ

	// 頂点フォーマットの設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));		
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, m_pTexture);									// テクスチャの設定

	// ポリゴンの描画
	pDevice->DrawPrimitive
	(
		D3DPT_TRIANGLESTRIP,
		0,																// 描画を開始する最初の頂点インデックス
		2																// ポリゴンの数
	);	

}

//------------------------------------------------------------
// 頂点座標の設定(不定形ポリゴンver.)
//------------------------------------------------------------
void CScene2D::SetPos(D3DXVECTOR3 vtx0, D3DXVECTOR3 vtx1, D3DXVECTOR3 vtx2, D3DXVECTOR3 vtx3)
{
	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// バッファの生成
	pVtx[0].pos = vtx0;
	pVtx[1].pos = vtx1;
	pVtx[2].pos = vtx2;
	pVtx[3].pos = vtx3;

	m_pVtxBuff->Unlock();
}

//------------------------------------------------------------
// 長方形ポリゴン(回転込み)
//------------------------------------------------------------
void CScene2D::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 *Rotvtx)
{
	CScene::SetPos(pos);
	CScene::SetScale(scale);

	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// バッファの生成
	pVtx[0].pos = D3DXVECTOR3(pos.x + Rotvtx[0].x, pos.y + Rotvtx[0].y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + Rotvtx[1].x, pos.y + Rotvtx[1].y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x + Rotvtx[2].x, pos.y + Rotvtx[2].y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + Rotvtx[3].x, pos.y + Rotvtx[3].y, 0.0f);

	m_pVtxBuff->Unlock();
}

//------------------------------------------------------------
// 長方形ポリゴン(trueでスクロール分を含ませる)
//------------------------------------------------------------
void CScene2D::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale, bool bScroll)
{
	D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);

	if (bScroll == true)
	{
		Pos = pos - CGame::GetScroll();
	}
	else
	{
		Pos = pos;
	}

	CScene::SetPos(Pos);
	CScene::SetScale(scale);

	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// バッファの生成
	pVtx[0].pos = D3DXVECTOR3(Pos.x - (scale.x / 2), Pos.y - (scale.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Pos.x + (scale.x / 2), Pos.y - (scale.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Pos.x - (scale.x / 2), Pos.y + (scale.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Pos.x + (scale.x / 2), Pos.y + (scale.y / 2), 0.0f);

	m_pVtxBuff->Unlock();
}

//--------------------------------------------------------------------
// pos原点左端
//--------------------------------------------------------------------
void CScene2D::SetScalePos(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CScene::SetPos(pos);
	CScene::SetScale(scale);

	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//バッファの生成
	pVtx[0].pos = D3DXVECTOR3(pos.x,			pos.y - scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + scale.x,	pos.y - scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x,			pos.y + scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + scale.x,	pos.y + scale.y, 0.0f);

	m_pVtxBuff->Unlock();

}

//------------------------------------------------------------
// テクスチャの設定
//------------------------------------------------------------
void CScene2D::SetTex(int nAnim, int nPartU)
{
	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f + (1.0f / nPartU)* nAnim,	  0.0f);
	pVtx[1].tex = D3DXVECTOR2(		 (1.0f / nPartU)*(nAnim + 1), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (1.0f / nPartU)* nAnim,	  1.0f);
	pVtx[3].tex = D3DXVECTOR2(		 (1.0f / nPartU)*(nAnim + 1), 1.0f);

	m_pVtxBuff->Unlock();

}
void CScene2D::SetTex(float nPatternX,float nPatternY, float fSizeX, float fSizeY)
{
	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nPatternX * fSizeX		 , nPatternY * fSizeY);
	pVtx[1].tex = D3DXVECTOR2(nPatternX * fSizeX + fSizeX, nPatternY * fSizeY);
	pVtx[2].tex = D3DXVECTOR2(nPatternX * fSizeX		 , nPatternY * fSizeY + fSizeY);
	pVtx[3].tex = D3DXVECTOR2(nPatternX * fSizeX + fSizeX, nPatternY * fSizeY + fSizeY);

	m_pVtxBuff->Unlock();

}
void CScene2D::SetTex(float fSpeedX, float fSpeedY)
{
	VERTEX_2D *pVtx;

	CScene::SetTex(D3DXVECTOR2(fSpeedX, fSpeedY));

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f + fSpeedX, 0.0f + fSpeedY);
	pVtx[1].tex = D3DXVECTOR2(1.0f + fSpeedX, 0.0f + fSpeedY);
	pVtx[2].tex = D3DXVECTOR2(0.0f + fSpeedX, 1.0f + fSpeedY);
	pVtx[3].tex = D3DXVECTOR2(1.0f + fSpeedX, 1.0f + fSpeedY);

	m_pVtxBuff->Unlock();
}

//------------------------------------------------------------
// カラーの設定
//------------------------------------------------------------
void CScene2D::SetCol(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

	m_pVtxBuff->Unlock();

}

//------------------------------------------------------------
// ポリゴンの移動計算
//------------------------------------------------------------
D3DXVECTOR3 CScene2D::Move(D3DXVECTOR3 *pPos, float angle, float speed)
{
	D3DXVECTOR3 move;
	float fAngle = angle;
	float fSpeed = speed;

	move.x = sinf(-fAngle) * fSpeed;
	move.y = cosf(-fAngle) * fSpeed;

	*pPos -= move;

	return move;
}
