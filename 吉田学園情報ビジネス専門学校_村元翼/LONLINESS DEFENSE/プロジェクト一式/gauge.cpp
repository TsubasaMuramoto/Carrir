//============================================================
// ゲージの処理
//============================================================
#include "main.h" 
#include "manager.h"
#include "renderer.h"
#include "gauge.h"
#include "fade.h"

//============================================================
// 静的メンバ変数の初期化
//============================================================
D3DXVECTOR3 CGauge::m_Scale = {};

//============================================================
// コンストラクタ
//============================================================
CGauge::CGauge(OBJTYPE nPriority) : CScene2D(nPriority)
{
	m_bNextMode = false;
	m_fScaleSpeed = 0.1f;
}

//============================================================
// デストラクタ
//============================================================
CGauge::~CGauge()
{

}

//============================================================
// ゲージの生成
//============================================================
CGauge *CGauge::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	// インスタンス生成
	CGauge *pGauge = new CGauge;

	if (pGauge != nullptr)
	{
		pGauge->m_pos = pos;
		pGauge->m_Scale = scale;
		pGauge->Init(pGauge->m_pos, pGauge->m_Scale);
	}

	return pGauge;
}

//============================================================
// 初期化
//============================================================
HRESULT CGauge::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CScene2D::BindTexture(CTexture::Gauge);
	CScene2D::Init();
	CScene2D::SetScalePos(pos, scale);
	CScene2D::SetCol(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

	return S_OK;
}

HRESULT CGauge::Init(void)
{
	return 0;
}

//============================================================
// 終了
//============================================================
void CGauge::Uninit()
{
	CScene2D::Uninit();
}

//============================================================
// 更新
//============================================================
void CGauge::Update()
{
	CScene2D::Update();
	CScene2D::SetScalePos(m_pos, m_Scale);
	//m_Scale.x += m_fScaleSpeed;//ゲージの上昇

	// ゲージの振り切り防止
	if (m_Scale.x <= 0)
	{
		m_Scale.x = 0.0f;
	}

	// ゲージがなくなる
	if (m_Scale.x <= 0.0f && m_bNextMode == false)
	{
		m_Scale.x = 0.0f;			
		CFade::SetFade(CManager::MODE_RESULT);	// リザルトへ行く
		m_bNextMode = true;						// 一回のみこの条件文を通す
	}

	if (m_Scale.x < MAX_GAUGE_WIDTH / 2)
	{
		CScene2D::SetCol(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	}
	if (m_Scale.x < MAX_GAUGE_WIDTH / 4)
	{
		CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}
}

//============================================================
// 描画
//============================================================
void CGauge::Draw()
{
	CScene2D::Draw();
}

//============================================================
// ゲージの設定
//============================================================
void CGauge::SetGauge(float Set)
{
	if (m_Scale.x <= MAX_GAUGE_WIDTH)
	{
		m_Scale.x += Set;
	}
}