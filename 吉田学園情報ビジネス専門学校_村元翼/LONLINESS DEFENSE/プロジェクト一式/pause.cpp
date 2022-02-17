//---------------------------------------------------
// ポーズの処理
//---------------------------------------------------
#include "pause.h"
#include "XInput.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "texture.h"
#include "polygon.h"
#include "fade.h"
#include "bg.h"

//--------------------------
// 静的メンバ変数の初期化
//----------------------------
CBg *CPause::m_pBg = nullptr;

//--------------------------
// コンストラクタ
//----------------------------
CPause::CPause(OBJTYPE nPriority) :CScene(nPriority)
{
	// メンバ変数の初期化
	memset(m_pPolygon, 0, sizeof(m_pPolygon));
	m_bNextMode = false;
	m_bUninit = false;
	m_nPauseType = 0;
	m_fAlpha = 0.0f;
	m_pCursor = nullptr;
}

//--------------------------
// デストラクタ
//----------------------------
CPause::~CPause()
{

}

//--------------------------
// 初期化
//----------------------------
HRESULT CPause::Init(void)
{
	// ポーズ背景の生成とカラーの設定
	m_pBg = CBg::Create(false, CTexture::MapFrame, CScene::OBJTYPE_PAUSE);
	m_pBg->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f));

	// 選択肢のポリゴン生成
	for (int nCnt = 0; nCnt < MAX_PAUSE; nCnt++)
	{
		if (m_pPolygon == nullptr)
		{
			m_pPolygon[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SELECT_HEIGHT + (PAUSE_INERVAL * 0), 0.0f), SELECT_SIZE, CTexture::GameBack, CScene::OBJTYPE_PAUSE);
			m_pPolygon[1] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SELECT_HEIGHT + (PAUSE_INERVAL * 1), 0.0f), SELECT_SIZE, CTexture::Retry, CScene::OBJTYPE_PAUSE);
			m_pPolygon[2] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SELECT_HEIGHT + (PAUSE_INERVAL * 2), 0.0f), SELECT_SIZE, CTexture::TitleBack, CScene::OBJTYPE_PAUSE);
		}
	}

	// カーソルのポリゴン生成
	if (m_pCursor == nullptr)
	{
		m_pCursor = CScene2D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + (PAUSE_INERVAL * 0), 0.0f), D3DXVECTOR3(50.0f, 100.0f, 0.0f), CTexture::Cursol, CScene::OBJTYPE_UI);
	}

	return S_OK;
}

//--------------------------
// 終了
//----------------------------
void CPause::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_PAUSE; nCnt++)
	{
		if (m_pPolygon[nCnt] != nullptr)
		{
			m_pPolygon[nCnt]->Uninit();
			delete m_pPolygon[nCnt];
		}

	}

	if (m_pCursor != nullptr)
	{
		m_pCursor->Uninit();
		delete m_pCursor;
		m_pCursor = nullptr;
	}

	// ポーズ背景の破棄
	if (m_pBg != nullptr)
	{
		m_pBg->Uninit();
		delete m_pBg;
		m_pBg = nullptr;
	}

	CManager::SetPause(false,false);	// ポーズの状態をfalseにする
	Release();							// オブジェクトの破棄
}

//--------------------------
// 更新
//--------------------------
void CPause::Update(void)
{
	// ゲームパッドの取得
	CXInput *pXInput = CManager::GetXInput();
	CInputkeyboard *pKey = CManager::GetKeyboard();

	// 上に行く
	if (pKey->GetTrigger(DIK_W) == true ||
		pXInput->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP) == true)
	{
		// ポーズのタイプをずらす
		m_nPauseType--;
		if (m_nPauseType < 0)
		{
			m_nPauseType = MAX_PAUSE - 1;
		}
	}

	// 下に行く
	if (pKey->GetTrigger(DIK_S) == true ||
		pXInput->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN) == true)
	{
		// ポーズのタイプをずらす
		m_nPauseType++;
		if (m_nPauseType >= MAX_PAUSE)
		{
			m_nPauseType = 0;
		}
	}

	// カーソルの位置を変える
	switch (m_nPauseType)
	{
	case 0:
		m_pCursor->SetPos(D3DXVECTOR3(m_pPolygon[0]->GetPos().x - m_pPolygon[0]->GetScale().x, m_pPolygon[0]->GetPos().y,0.0f),m_pCursor->GetScale());
		break;

	case 1:
		m_pCursor->SetPos(D3DXVECTOR3(m_pPolygon[1]->GetPos().x - m_pPolygon[1]->GetScale().x, m_pPolygon[1]->GetPos().y, 0.0f), m_pCursor->GetScale());
		break;

	case 2:
		m_pCursor->SetPos(D3DXVECTOR3(m_pPolygon[2]->GetPos().x - m_pPolygon[2]->GetScale().x, m_pPolygon[2]->GetPos().y, 0.0f), m_pCursor->GetScale());
		break;

	}

	// 選択を決定する
	if ((pKey->GetTrigger(DIK_RETURN) == true || pXInput->GetButtonTrigger(XINPUT_GAMEPAD_A) == true) && m_bNextMode == false)
	{
		switch (m_nPauseType)
		{
		case 0:	//ゲームに戻る
			CManager::SetPause(false,false);
			break;
		case 1:	//リトライ
			CFade::SetFade(CManager::MODE_GAME);
			break;
		case 2:	//タイトル画面
			CFade::SetFade(CManager::MODE_TITLE);
			break;
		}
		m_bNextMode = true;
	}

	//---------------------------------------------------------------//
	// Uninitが呼ばれるとSceneでの更新が止まるから一回のみ通る仕組み //
	//---------------------------------------------------------------//
	//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ //
	// ポーズ状態がfalseなら
	if (CManager::GetPause() == false)
	{
		m_bUninit = true;	// 
	}

	if (m_bUninit == true)
	{
		Uninit();
	}

}

//--------------------------
// 描画
//----------------------------
void CPause::Draw(void)
{
	
}

//---------------------------------------------------------------
// インスタンス生成処理
//---------------------------------------------------------------
CPause *CPause::Create(D3DXVECTOR3 pos)
{
	// インスタンス生成
	CPause *pPause = nullptr;
	if (pPause == nullptr)
	{
		pPause = new CPause(OBJTYPE_PAUSE);	// メモリ確保
		if (pPause != nullptr)
		{
			pPause->m_pos = pos;
			pPause->Init();
		}
	}

	return pPause;
}
