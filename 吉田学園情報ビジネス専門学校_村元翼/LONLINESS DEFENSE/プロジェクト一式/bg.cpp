//---------------------------------------------------
// 背景の処理
//---------------------------------------------------
#include "bg.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "keyboard.h"
#include "player.h"
#include "game.h"

//--------------------------
// 静的メンバ変数初期化
//----------------------------
const D3DXVECTOR2 CBg::m_SpreadRange_min =  D3DXVECTOR2(0.0f, 0.0f);
const D3DXVECTOR2 CBg::m_SpreadRange_max =  D3DXVECTOR2(SCREEN_WIDTH,SCREEN_HEIGHT);

//--------------------------
// コンストラクタ
//----------------------------
CBg::CBg(OBJTYPE nPriority):CScene2D(nPriority)
{
	m_Tex = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bScroll = false;
	m_bCanScroll = false;
}

//--------------------------
// デストラクタ
//----------------------------
CBg::~CBg()
{

}

//--------------------------
// 初期化
//----------------------------
HRESULT CBg::Init()
{
	CScene2D::BindTexture(m_Type);
	CScene2D::Init();
	CScene2D::SetPos
	(
		D3DXVECTOR3(0.0f,0.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH,0.0f, 0.0f),
		D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f)
	);
	CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//--------------------------
// 終了
//----------------------------
void CBg::Uninit(void)
{
	CScene2D::Uninit();
}

//--------------------------
// 更新
//----------------------------
void CBg::Update(void)
{
	CScene2D::Update();
	BgLimit();

	if (m_bCanScroll == true)
	{
		m_pos += CGame::GetScroll();				// 実際にスクロールした量
		m_Tex += CGame::GetScroll() * 0.001f;		// 背景スピードを取得&調整
		CScene2D::SetTex(m_Tex.x, m_Tex.y);			// テクスチャ更新
	}	
}

//--------------------------
//描画
//----------------------------
void CBg::Draw(void)
{
	CScene2D::Draw();
}

//---------------------------------------------------------------
//インスタンス生成処理
//---------------------------------------------------------------
CBg *CBg::Create(bool bScrol,CTexture::Type type, CScene::OBJTYPE objtype)
{
	//インスタンス生成
	CBg *pBg = new CBg(objtype);

	if (pBg != NULL)
	{
		// 情報の取得
		pBg->m_Type = type;
		pBg->m_bCanScroll = bScrol;

		// 初期化処理
		pBg->Init();
	}
	return pBg;
}

//---------------------------------------------------------------
// 背景移動の限界値
//---------------------------------------------------------------
void CBg::BgLimit(void)
{
	//--------------------------
	// 背景スクロール範囲
	//----------------------------
	if (m_pos.x >= m_SpreadRange_max.x)	// 最大拡大Ｘ
	{
		m_pos.x = m_SpreadRange_max.x;
	}
	if (m_pos.x <= m_SpreadRange_min.x)	// 最小拡大Ｘ
	{
		m_pos.x = m_SpreadRange_min.x;
	}
	if (m_pos.y >= m_SpreadRange_max.y)	// 最大拡大Ｙ
	{
		m_pos.y = m_SpreadRange_max.y;
	}
	if (m_pos.y <= m_SpreadRange_min.y)	// 最小拡大Ｙ
	{
		m_pos.y = m_SpreadRange_min.y;
	}
}

