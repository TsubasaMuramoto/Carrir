//--------------------------------------
// マネージャーの処理
//--------------------------------------
#include "title.h"
#include "bg.h"
#include "texture.h"
#include "manager.h"
#include "keyboard.h"
#include "fade.h"
#include "polygon.h"
#include "XInput.h"

//--------------------------------------------
// コンストラクタ
//--------------------------------------------
CTitle::CTitle()
{
	// メンバ変数の初期化
	memset(m_pTitle, 0, sizeof(m_pTitle));
	m_bNextMode = false;
	m_nFrame = 0;
	m_nMultiFrame = 1;
}

//--------------------------------------------
// デストラクタ
//--------------------------------------------
CTitle::~CTitle()
{

}

//--------------------------------------------
//初期化
//--------------------------------------------
HRESULT CTitle::Init(void)
{
	CBg::Create(false ,CTexture::Target,CScene::OBJTYPE_BG);	//背景

	m_pTitle[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f, 0.0f), D3DXVECTOR3(1000.0f, 300.0f, 0.0f), CTexture::Title, CScene::OBJTYPE_BG);
	m_pTitle[1] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 500.0f, 0.0f), D3DXVECTOR3(600.0f, 200.0f, 0.0f), CTexture::PressEnter,CScene::OBJTYPE_BG);
	//m_Polygon[0] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH/2.0f, SCREEN_HEIGHT / 2 - 280.0f, 0.0f), D3DXVECTOR3(430.0f, 80.0f, 0.0f), CTexture::Titlelogo);	//タイトルロゴ
	//m_Polygon[1] = CPolygon::Create(D3DXVECTOR3(900.0f, SCREEN_HEIGHT / 2 + 50.0f, 0.0f), D3DXVECTOR3(300.0f, 80.0f, 0.0f), CTexture::GameStart);	//ゲームスタート
	//m_Polygon[2] = CPolygon::Create(D3DXVECTOR3(900.0f, SCREEN_HEIGHT / 2 + 250, 0.0f), D3DXVECTOR3(300.0f, 40.0f, 0.0f), CTexture::Operation);	//チュートリアル
	//m_Cursol = CPolygon::Create(D3DXVECTOR3(900.0f, SCREEN_HEIGHT / 2 + 250, 0.0f), D3DXVECTOR3(40.0f, 40.0f, 0.0f), CTexture::Cursol);	//カーソル

	return S_OK;
}

//--------------------------------------------
//終了
//--------------------------------------------
void CTitle::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_TITLE_POLYGON; nCnt++)
	{
		if (m_pTitle[nCnt] != nullptr)
		{
			m_pTitle[nCnt]->Uninit();
			delete m_pTitle[nCnt];
			m_pTitle[nCnt] = nullptr;
		}
	}
}

//--------------------------------------------
//更新
//--------------------------------------------
void CTitle::Update(void)
{
	CInputkeyboard *pKey = CManager::GetKeyboard();
	CXInput *pGamePad = CManager::GetXInput();

	// press start点滅処理
	if (m_pTitle[1] != nullptr)
	{
		m_nFrame++;
		if (m_nFrame > (BLINK_INTERVAL / 2) / m_nMultiFrame && m_nFrame <= BLINK_INTERVAL / m_nMultiFrame)
		{
			m_pTitle[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}

		else if (m_nFrame > BLINK_INTERVAL / m_nMultiFrame)
		{
			m_pTitle[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_nFrame = 0;
		}
	}

	// ENTERを押す
	if (pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_START) || pKey->GetTrigger(DIK_RETURN) == true && m_bNextMode == false)
	{
		m_nMultiFrame = BLINK_SPEED;
		CFade::SetFade(CManager::MODE_TUTORIAL);		// ゲームモードへ
		m_bNextMode = true;								// ENTER連打防止
	}
}

//--------------------------------------------
//描画
//--------------------------------------------
void CTitle::Draw(void)
{

}

