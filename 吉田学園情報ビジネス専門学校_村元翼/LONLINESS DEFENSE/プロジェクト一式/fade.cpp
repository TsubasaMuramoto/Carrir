//-------------------------------------------------------------------
// フェードの処理
//-------------------------------------------------------------------
#include "fade.h"
#include "bg.h"
#include "texture.h"
#include "manager.h"
#include "scene2D.h"

//-------------------------------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------------------------------
CFade::FADE					CFade::m_fade = CFade::FADE_IN;
CManager::MODE				CFade::m_modeNext = CManager::GetInstance()->MODE_TITLE;
float						CFade::m_colorAlpha = 1.0f;
CBg							*CFade::m_pBg = nullptr;

//--------------------------------------------
// コンストラクタ
//--------------------------------------------
CFade::CFade(OBJTYPE nPriority) :CScene(nPriority)
{
	
}

//--------------------------------------------
// デストラクタ
//--------------------------------------------
CFade::~CFade()
{

}

//---------------------------------------------------------------
// インスタンス生成処理
//---------------------------------------------------------------
CFade *CFade::Create(CTexture::Type type, CManager::MODE modeNext)
{
	//インスタンス生成
	CFade *pFade = new CFade(OBJTYPE_FADE);

	if (pFade != NULL)
	{
		pFade->m_modeNext = modeNext;
		pFade->m_Type = type;
		pFade->Init();
	}
	return pFade;
}

//--------------------------------------------
// 初期化
//--------------------------------------------
HRESULT CFade::Init(void)
{
	// 背景生成
	m_pBg = CBg::Create(false,CFade::m_Type,CScene::OBJTYPE_FADE);

	return S_OK;
}

//--------------------------------------------
// 終了
//--------------------------------------------
void CFade::Uninit(void)
{
	Release();
}

//--------------------------------------------
// 更新
//--------------------------------------------
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		m_pBg->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colorAlpha));

		// フェード画面を消す
		if (m_fade == FADE_IN)
		{
			m_colorAlpha -= 0.05f;
			if (m_colorAlpha <= 0.0f)
			{
				m_colorAlpha = 0.0f;
				m_fade = FADE_NONE;
			}

		}
		// フェード画面を出す
		else if (m_fade == FADE_OUT)
		{
			m_colorAlpha += 0.01f;

			if (m_colorAlpha >= 1.0f)
			{
				m_colorAlpha = 1.0f;
				m_fade = FADE_IN;

				// モードの設定
				CManager::GetInstance()->SetMode(m_modeNext);
			}
		}
	}
}

//--------------------------------------------
// 描画
//--------------------------------------------
void CFade::Draw(void)
{

}

//--------------------------------------------
// フェードの設定処理
//--------------------------------------------
void CFade::SetFade(CManager::MODE modeNext)
{
	m_fade = FADE_OUT;
	m_modeNext = modeNext;
	m_colorAlpha = 0.0f;
}

//--------------------------------------------
// フェードの取得処理
//--------------------------------------------
CFade::FADE CFade::GetFade(void)
{
	return m_fade;
}
