//--------------------------------------
// チュートリアルの処理
//--------------------------------------
#include "Tutorial.h"
#include "bg.h"
#include "texture.h"
#include "manager.h"
#include "keyboard.h"
#include "fade.h"
#include "polygon.h"
#include "XInput.h"
#include "sound.h"

//--------------------------------------------
// コンストラクタ
//--------------------------------------------
CTutorial::CTutorial()
{
	// メンバ変数の初期化
	memset(m_pTutorial, 0, sizeof(m_pTutorial));
	m_bNextMode = false;
}
//--------------------------------------------
// デストラクタ
//--------------------------------------------
CTutorial::~CTutorial()
{

}

//--------------------------------------------
// 初期化
//--------------------------------------------
HRESULT CTutorial::Init(void)
{
	CBg::Create(false, CTexture::Bg, CScene::OBJTYPE_BG);	// 背景

	// チュートリアルページの１枚目
	m_pTutorial[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 350.0f, 0.0f), D3DXVECTOR3(1000.0f, 600.0f, 0.0f), CTexture::Tutorial01, CScene::OBJTYPE_BG);

	return S_OK;
}
//--------------------------------------------
// 終了
//--------------------------------------------
void CTutorial::Uninit(void)
{
	// メンバ変数の終了
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pTutorial[nCnt]->Uninit();
		delete m_pTutorial[nCnt];
		m_pTutorial[nCnt] = nullptr;
	}
}
//--------------------------------------------
// 更新
//--------------------------------------------
void CTutorial::Update(void)
{
	// 入力デバイスの取得
	CInputkeyboard *pKey = CManager::GetInstance()->GetKeyboard();
	CXInput *pGamePad = CManager::GetInstance()->GetXInput();
	CSound *pSound = CManager::GetInstance()->GetSound();

	// Enterでモード変更
	if ((pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_START) || pKey->GetTrigger(DIK_RETURN)) && !m_bNextMode && m_pTutorial[1] != nullptr)
	{
		CFade::SetFade(CManager::MODE_GAME);				// ゲームモードへ
		m_bNextMode = true;									// ENTER連打防止
		pSound->PlaySound(pSound->SOUND_LABEL_SE_DECIDE);	// 決定音
	}

	// ページを変える
	else if((pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_START) || pKey->GetTrigger(DIK_RETURN) == true) && m_pTutorial[1] == nullptr)
	{
		m_pTutorial[0]->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		m_pTutorial[1] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 350.0f, 0.0f), D3DXVECTOR3(1000.0f, 600.0f, 0.0f), CTexture::Tutorial02, CScene::OBJTYPE_BG);
		pSound->PlaySound(pSound->SOUND_LABEL_SE_ENTER);	// 決定音
	}
}
//--------------------------------------------
// 描画
//--------------------------------------------
void CTutorial::Draw(void)
{

}

