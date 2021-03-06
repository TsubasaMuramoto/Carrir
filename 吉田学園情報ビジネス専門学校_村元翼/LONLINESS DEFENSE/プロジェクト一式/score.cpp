//--------------------------------------------------------------
// スコアの作成
// Author
//--------------------------------------------------------------
#include "main.h"
#include "manager.h"
#include "keyboard.h"
#include "scene.h"
#include "scene2D.h"
#include "score.h"
#include "texture.h"
#include "number.h"
#include "play_data.h"

//---------------------------------------------------
// 静的メンバ変数の初期化
//---------------------------------------------------

//---------------------------------------------------
// コンストラクタ
//---------------------------------------------------
CScore::CScore(OBJTYPE nPriority) : CScene(nPriority)
{

}

//---------------------------------------------------
// デストラクタ
//---------------------------------------------------
CScore::~CScore()
{
}

//---------------------------------------------------
// スコアの生成
//---------------------------------------------------
CScore *CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// インスタンス生成
	CScore *pScore = NULL;
	pScore = new CScore;

	if (pScore != NULL)
	{
		pScore->Init(pos, size);	// 初期化
	}

	return pScore;
}

//---------------------------------------------------
// 初期化
//---------------------------------------------------
HRESULT CScore::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCntTime = 0; nCntTime < MAX_SCORE; nCntTime++)
	{
		m_apNumber[nCntTime] = CNumber::Create(D3DXVECTOR3(pos.x + nCntTime * 50, pos.y, pos.z), size);
		m_apNumber[nCntTime]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_nAll++;
	}

	m_pos = pos;
	m_size = size;
	m_nAddScore = 10;	// 加算するスコアの初期化
	m_nScore = 0;		// スコアの初期化

	SetPos(m_pos);
	SetScale(m_size);
	return S_OK;
}

HRESULT CScore::Init(void)
{
	return 0;
}

//---------------------------------------------------
// 終了
//---------------------------------------------------
void CScore::Uninit()
{
	// ナンバーの破棄
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (m_apNumber != nullptr)
		{
			m_apNumber[nCnt]->Uninit();
			m_apNumber[nCnt] = nullptr;
		}
	}

	CPlayData::SetScore(m_nScore);
	m_nAll = 0;
	Release();
}

//---------------------------------------------------
// 更新
//---------------------------------------------------
void CScore::Update()
{
#if _DEBUG
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_0))
	{
		AddScore(m_nAddScore);	// スコアの加算
	}
#endif

	SetScore();
}

//---------------------------------------------------
// 描画
//---------------------------------------------------
void CScore::Draw()
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (m_apNumber[nCnt] != nullptr)
		{
			m_apNumber[nCnt]->Draw();
		}
	}
}

//---------------------------------------------------
// スコアの設定
//---------------------------------------------------
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
}

//---------------------------------------------------
// スコアの設定
//---------------------------------------------------
void CScore::SetScore()
{
	for (int nCnt = 0, nDecrement = 1; nCnt < m_nAll; nCnt++, nDecrement *= 10)
	{
		m_apNumber[nCnt]->SetNumber(m_nScore % ((int)pow(10, m_nAll) / nDecrement) / ((int)pow(10, m_nAll - 1) / nDecrement));
	}

	//for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	//{
	//	if (nCnt == 0)										// 1桁目
	//	{
	//		m_apNumber[nCnt]->SetNumber(m_nScore / (int)pow(10, MAX_SCORE - 1));
	//	}
	//	else if (nCnt == MAX_SCORE - 1)						// 最後の桁
	//	{
	//		m_apNumber[nCnt]->SetNumber(m_nScore % 10);
	//	}
	//	else												// それ以外の桁
	//	{
	//		m_apNumber[nCnt]->SetNumber(m_nScore % (int)pow(10, MAX_SCORE - (float)nCnt) / (int)pow(10, MAX_SCORE - 1 - (float)nCnt));
	//	}
	//}
}

//================================================
//スコア位置設定処理
//================================================
void CScore::SetScorePos(D3DXVECTOR3 pos)
{
	//位置設定
	m_pos = pos;
	for (int nCntNumber = 0; nCntNumber < MAX_SCORE; nCntNumber++)
	{
		//小数点をつけるため、4つ目の数字からずらす
		m_apNumber[nCntNumber]->SetPos(D3DXVECTOR3(pos.x - (m_size.x * MAX_SCORE / 2) + (m_size.x * nCntNumber) + (m_size.x / 2.0f), pos.y, 0.0f));
	}
	//位置を設定
	SetPos(m_pos);
}

