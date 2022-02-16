//---------------------------------------------------------------
// タイムの作成
//
//---------------------------------------------------------------
#include "main.h" 
#include "manager.h"
#include "number.h"
#include "renderer.h"
#include "time.h"
#include "fade.h"

//---------------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------------
CTime::CTime(OBJTYPE nPriority) : CScene(nPriority)
{
}

//---------------------------------------------------------------
// デストラクタ
//---------------------------------------------------------------
CTime::~CTime()
{
}

//---------------------------------------------------------------
// タイムの生成
//---------------------------------------------------------------
CTime *CTime::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// インスタンス生成
	CTime *pTime = nullptr;

	if (pTime == nullptr)
	{
		pTime = new CTime;

		if (pTime != nullptr)
		{
			pTime->Init(pos, size);	// 初期化
		}
	}

	return pTime;
}

//---------------------------------------------------------------
// 初期化
//---------------------------------------------------------------
HRESULT CTime::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ポリゴンの生成
	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		m_apNumber[nCntTime] = CNumber::Create(D3DXVECTOR3(pos.x + nCntTime * size.x, pos.y, pos.z), size);
		m_apNumber[nCntTime]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_nAll++;
	}

	m_bNextMode = false;
	m_nFrame = 0;	// フレーム初期化
	m_nTime = TIME;	// 制限時間の設定
	return S_OK;
}

HRESULT CTime::Init(void)
{
	return 0;
}

//---------------------------------------------------------------
// 終了
//---------------------------------------------------------------
void CTime::Uninit()
{
	m_nAll++;
	Release();	// インスタンス破棄
}

//---------------------------------------------------------------
// 更新
//---------------------------------------------------------------
void CTime::Update()
{
	m_nFrame++;// フレームを回す
	// 60フレーム回ったら
	if (m_nFrame >= 60)
	{
		m_nFrame = 0;	// フレーム初期化
		m_nTime -= 1;	// タイムを1秒減らす
	}

	// 20秒以下になったら赤色にする
	if (m_nTime <= 20)
	{
		for (int nCnt = 0; nCnt < m_nAll; nCnt++)
		{
			m_apNumber[nCnt]->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));	// カラーの設定
		}
	}

	// 0秒より低くならないようにする
	if (m_nTime <= 0 && m_bNextMode == false)
	{
		m_nTime = 0;
		CFade::SetFade(CManager::MODE_RESULT);
		m_bNextMode = true;
	}

	SetTime();//描画の設定
}

//---------------------------------------------------------------
// 描画
//---------------------------------------------------------------
void CTime::Draw()
{
	for (int nCntTime =0; nCntTime < m_nAll; nCntTime++)
	{
		if (m_apNumber[nCntTime] != nullptr)
		{
			m_apNumber[nCntTime]->Draw();
		}
	}
}

//---------------------------------------------------------------
// 描画の設定
//---------------------------------------------------------------
void CTime::SetTime()
{
	for (int nCnt = 0, nDecrement = 1; nCnt < m_nAll; nCnt++, nDecrement *= 10)
	{
		m_apNumber[nCnt]->SetNumber(m_nTime % ((int)pow(10, m_nAll) / nDecrement) / ((int)pow(10, m_nAll - 1) / nDecrement));
	}

	//int aTime[MAX_TIME];

	//aTime[0] = m_nTime % 1000 / 100;	// 60%1000=60, 60/100=0
	//aTime[1] = m_nTime % 100 / 10;	// 60%100=60,  60/10=6
	//aTime[2] = m_nTime % 10 / 1;		// 60%10=0,    0/1=0

	//for (int nCntTime = 0,nDecrement = 1; nCntTime < m_nAll; nCntTime++,nDecrement *= 10)
	//{
	//	aTime[nCntTime] = m_nTime % (1000 / nDecrement) / (100 / nDecrement);	// nCnt目の桁計算
	//}

	//for (int nCntTime = 0; nCntTime < m_nAll; nCntTime++)
	//{
	//	m_apNumber[nCntTime]->SetTex((float)aTime[nCntTime],0.0f, 0.1f,1.0f);
	//}
}