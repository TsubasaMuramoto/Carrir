//--------------------------------------
// マネージャーの処理
//--------------------------------------
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "polygon.h"
#include "player.h"
#include "keyboard.h"
#include "enemy.h"
#include "bg.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "pause.h"
#include "mouse.h"
#include "XInput.h"
#include "play_data.h"
#include "sound.h"

//--------------------------------------
//静的メンバ変数宣言
//--------------------------------------
CRenderer		*CManager::m_pRenderer = nullptr;
CTexture		*CManager::m_pTexture = nullptr;
CInputkeyboard	*CManager::m_pKeyboard = nullptr;
CGame			*CManager::m_pGame = nullptr;
CTitle			*CManager::m_pTitle = nullptr;
CTutorial		*CManager::m_pTutorial = nullptr;
CResult			*CManager::m_pResult = nullptr;
CFade			*CManager::m_pFade = nullptr;
CPause			*CManager::m_pPause = nullptr;
CMouse			*CManager::m_pMouse = nullptr;
CXInput			*CManager::m_pXInput = nullptr;
CPlayData		*CManager::m_pPlayData = nullptr;
CSound			*CManager::m_pSound = nullptr;
bool			CManager::m_bGamepadSwitch = false;
bool			CManager::m_bStop = false;
bool			CManager::m_bPause = false;

#ifdef _DEBUG
CManager::MODE	CManager::m_Mode = MODE_GAME;	// デバッグモード時に通る
#endif

#ifndef _DEBUG
CManager::MODE	CManager::m_Mode = MODE_TITLE;	// リリースモード時に通る
#endif

//--------------------------------------------
//コンストラクタ
//--------------------------------------------
CManager::CManager()
{
}

//--------------------------------------------
//デストラクタ
//--------------------------------------------
CManager::~CManager()
{
}

//--------------------------------------------
// 初期化
//--------------------------------------------
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// サウンドの生成
	if(m_pSound == nullptr)
	{ 
		m_pSound = new CSound;

		if (m_pSound != nullptr)
		{
			m_pSound->Init(hWnd);
		}
	}

	//プレイデータクラスの生成
	if (m_pPlayData == nullptr)
	{
		m_pPlayData = new CPlayData;

		if (m_pPlayData != nullptr)
		{
			m_pPlayData->Init();
		}
	}

	// レンダラーの生成
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new CRenderer;

		if (m_pRenderer != nullptr)
		{
			if (FAILED(m_pRenderer->Init(hInstance, hWnd, bWindow)))
			{
				return -1;
			}
		}
	}

	// テクスチャの生成と初期化
	if (m_pTexture == nullptr)
	{
		m_pTexture = new CTexture;

		if (m_pTexture != nullptr)
		{
			m_pTexture->Init();
		}
	}

	// キーボードの生成と初期化
	if (m_pKeyboard == nullptr)
	{
		m_pKeyboard = new CInputkeyboard;

		if (m_pKeyboard != nullptr)
		{
			m_pKeyboard->Init(hInstance, hWnd);
		}
	}

	// マウスの生成と初期化
	if (m_pMouse == nullptr)
	{
		m_pMouse = new CMouse;

		if (m_pMouse != nullptr)
		{
			m_pMouse->Init(hInstance, hWnd);
		}
	}

	// Xinputの生成
	if (m_pXInput == nullptr)
	{
		m_pXInput = new CXInput;
	}

	// モードの設定
	SetMode(m_Mode);

	// フェードの生成
	if (m_pFade == nullptr)
	{
		m_pFade = CFade::Create(CTexture::Gauge, m_Mode);
	}
	
	//-----------------------------------------
	// 各種オブジェクトの生成
	//-----------------------------------------
	return S_OK;
}
//--------------------------------------------
// 終了
//--------------------------------------------
void CManager::Uninit(void)
{
	// オブジェクトの破棄
	CScene::ReleaseAll();

	// Xinputの破棄
	if (m_pXInput != nullptr)
	{
		delete m_pXInput;
		m_pXInput = nullptr;
	}

	// マウスの破棄
	if (m_pMouse != nullptr)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = nullptr;
	}

	// キーボードの破棄
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	// テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Uninit();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	// フェードの破棄
	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}

	// レンダラーの破棄
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	// プレイデータの破棄
	if (m_pPlayData != nullptr)
	{
		m_pPlayData->Uninit();
		delete m_pPlayData;
		m_pPlayData = nullptr;
	}

	// プレイデータの破棄
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}
}
//--------------------------------------------
// 更新
//--------------------------------------------
void CManager::Update(void)
{
	// レンダラーの更新
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}

	// キーボードの更新
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Update();
	}

	// マウスの更新
	if (m_pMouse != nullptr)
	{
		m_pMouse->Update();
	}


	// ゲームパッドの更新
	if (m_pXInput != nullptr)
	{
		m_pXInput->UpdateGamepad();
	}


	// モード毎の更新
	switch (m_Mode)
	{
	case MODE_TITLE:		// タイトル画面
		if (m_pTitle != nullptr)
		{
			m_pTitle->Update();
		}
		break;

	case MODE_TUTORIAL:		// チュートリアル画面
		if (m_pTutorial != nullptr)
		{
			m_pTutorial->Update();
		}
		break;

	case MODE_GAME:			// ゲーム画面
		if (m_pGame != nullptr)
		{
			m_pGame->Update();

			// ポーズ切り替え(Pを押す)
			if (GetKeyboard()->GetTrigger(DIK_P)|| GetXInput()->GetButtonTrigger(XINPUT_GAMEPAD_START))
			{
				m_bStop = !m_bStop;			// ストップを切り替える

				m_bPause = !m_bPause;		// ポーズを切り替える
			}

			// ストップ状態
			if (m_bStop)
			{
				// コントローラーのバイブレーションと止める
				m_pXInput->SetVibration(0, 0);

				// ポーズの生成
				if (m_pPause == nullptr)
				{
					m_pPause = CPause::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
			}

			else
			{
				// ポーズをNULLにする
				if (m_pPause != nullptr)
				{
					// deleteはSceneで行う
					m_pPause->Uninit();
					m_pPause = nullptr;
				}
			}

		}
		break;

	case MODE_RESULT:		//リザルト画面
		if (m_pResult != nullptr)
		{
			m_pResult->Update();
		}
		break;
	}
}
//--------------------------------------------
// 描画
//--------------------------------------------
void CManager::Draw(void)
{
	// レンダラーの描画
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Draw();
	}

	// モード毎の描画
	switch (m_Mode)
	{
	case MODE_TITLE:		// タイトル画面
		if (m_pTitle != nullptr)
		{
			m_pTitle->Draw();
		}
		break;

	case MODE_TUTORIAL:		// チュートリアル画面
		if (m_pTutorial != nullptr)
		{
			m_pTutorial->Draw();
		}
		break;

	case MODE_GAME:			// ゲーム画面
		if (m_pGame != nullptr)
		{
			m_pGame->Draw();
		}
		break;

	case MODE_RESULT:		// リザルト画面
		if (m_pResult != nullptr)
		{
			m_pResult->Draw();
		}
		break;
	}
}

//-----------------------------------------------------------------------------
// モードの処理
//-----------------------------------------------------------------------------
void CManager::SetMode(MODE mode)
{
	//m_bEnd = false;

	// 現在のモードを破棄
	switch (m_Mode)
	{
	case MODE_TITLE:		//タイトル画面
		if (m_pTitle != nullptr)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = nullptr;
		}
		break;

	case MODE_TUTORIAL:		// チュートリアル画面
		if (m_pTutorial != nullptr)
		{
			m_pTutorial->Uninit();
			delete m_pTutorial;
			m_pTutorial = nullptr;
		}
		break;

	case MODE_GAME:			// ゲーム画面
		if (m_pGame != nullptr)
		{
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = nullptr;
		}

		if (m_pPause != nullptr)
		{
			m_pPause->Uninit();
			delete m_pPause;
			m_pPause = nullptr;
		}
		break;

	case MODE_RESULT:		//リザルト画面
		if (m_pResult != nullptr)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = nullptr;
		}
		break;
	}

	//現在のモードで生成したオブジェクトの削除
	CScene::ReleaseAll();

	// 次に移行するモードの生成
	switch (mode)
	{
	case MODE_TITLE:		//タイトル画面
		if (m_pTitle == nullptr)
		{
			m_pTitle = new CTitle;
			m_pTitle->Init();
		}
		break;

	case MODE_TUTORIAL:		// チュートリアル画面
		if (m_pTutorial == nullptr)
		{
			m_pTutorial = new CTutorial;
			m_pTutorial->Init();
		}
		break;

	case MODE_GAME:			//ゲーム画面
		if (m_pGame == nullptr)
		{
			m_bPause = false;
			m_bStop = false;

			m_pGame = new CGame;
			m_pGame->Init();
		}
		break;
	case MODE_RESULT:		//リザルト画面
		if (m_pResult == nullptr)
		{
			m_pResult = new CResult;
			m_pResult->Init();
		}
		break;
	}

	//次のモードを現在のモードに上書き
	m_Mode = mode;
}