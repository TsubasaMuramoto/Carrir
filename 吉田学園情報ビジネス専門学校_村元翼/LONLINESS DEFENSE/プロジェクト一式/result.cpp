//--------------------------------------
// リザルト画面の処理
//--------------------------------------
#include "result.h"
#include "manager.h"
#include "keyboard.h"
#include "fade.h"
#include "ranking.h"
#include "XInput.h"
#include "sound.h"

//--------------------------------------------
// コンストラクタ
//--------------------------------------------
CResult::CResult()
{
	m_bNextMode = false;
}
//--------------------------------------------
// デストラクタ
//--------------------------------------------
CResult::~CResult()
{

}

//--------------------------------------------
// 初期化
//--------------------------------------------
HRESULT CResult::Init(void)
{
	//ランキングの生成
	m_pRanking = CRanking::Create
	(
		D3DXVECTOR3(500.0f + RANKING_POLYGON_WIDTH * MAX_SCORE, RESULT_RANKING_POSY, 0.0f),
		D3DXVECTOR3(RANKING_POLYGON_WIDTH, RANKING_POLYGON_HEIGHT, 0.0f)
	);																																					//m_pBg->SetCol(D3DXCOLOR(0.0, 0.0, 1.0, 1.0));

	return S_OK;
}
//--------------------------------------------
// 終了
//--------------------------------------------
void CResult::Uninit(void)
{
	if (m_pRanking != nullptr)
	{
		m_pRanking->Uninit();
		m_pRanking = nullptr;
	}
}
//--------------------------------------------
// 更新
//--------------------------------------------
void CResult::Update(void)
{
	// 入力デバイスの取得
	CInputkeyboard *pKey = CManager::GetKeyboard();
	CXInput *pGamePad = CManager::GetXInput();	

	// ENTERを押す
	if (pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_START) || pKey->GetTrigger(DIK_RETURN) && !m_bNextMode)
	{
		CFade::SetFade(CManager::MODE_TITLE);			// ゲームモードへ
		m_bNextMode = true;								// ENTER連打防止
	}
}
//--------------------------------------------
// 描画
//--------------------------------------------
void CResult::Draw(void)
{

}

