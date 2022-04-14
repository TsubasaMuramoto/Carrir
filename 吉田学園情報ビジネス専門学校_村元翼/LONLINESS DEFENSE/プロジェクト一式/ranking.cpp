//================================================
//ランキング処理
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "score.h"
#include "manager.h"
#include "ranking.h"
#include "play_data.h"
#include "number.h"
#include "result.h"
#include "texture.h"
#include "keyboard.h"

//================================================
//静的メンバ変数宣言
//================================================
CScore *CRanking::m_apScore[MAX_RANKING] = {};

//================================================
//デフォルトコンストラクタ
//================================================
CRanking::CRanking()
{
	for (int nCntRanking = 0; nCntRanking < MAX_SCORE_DATA; nCntRanking++)
	{
		m_nScore[nCntRanking] = 0;
	}
	m_nNowScore = 0;
	m_col.r = 0.0f;
	m_col.g = 0.0f;
	m_col.b = 0.0f;
	m_col.a = 0.0f;
	m_bClear = false;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CRanking::~CRanking()
{

}

//================================================
//初期化処理
//================================================
HRESULT CRanking::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		//スコアの生成
		m_apScore[nCntRanking] = CScore::Create
		(
			D3DXVECTOR3
			(
				pos.x,
				pos.y + (float)(SCREEN_HEIGHT / (MAX_RANKING + 1)) * nCntRanking + (float)(SCREEN_HEIGHT / (MAX_RANKING + 1)),
				0.0f
			),
			size
		);

		// ランク生成
		m_apScene2D[nCntRanking] = CScene2D::Create
		(
			D3DXVECTOR3
			(
				RANKING_RANK_POLYGON_POS_X,
				pos.y + (float)(SCREEN_HEIGHT / (MAX_RANKING + 1)) * nCntRanking + (float)(SCREEN_HEIGHT / (MAX_RANKING + 1)),
				0.0f
			),
			RANKING_RANK_POLYGON_SIZE
		);

		switch (nCntRanking)
		{
		case 0:
			m_apScene2D[nCntRanking]->BindTexture(CManager::GetTexture()->Rank1);

			break;
		case 1:
			m_apScene2D[nCntRanking]->BindTexture(CManager::GetTexture()->Rank2);
			break;
		case 2:
			m_apScene2D[nCntRanking]->BindTexture(CManager::GetTexture()->Rank3);
			break;
		case 3:
			m_apScene2D[nCntRanking]->BindTexture(CManager::GetTexture()->Rank4);
			break;
		case 4:
			m_apScene2D[nCntRanking]->BindTexture(CManager::GetTexture()->Rank5);
			break;
		}
	}

	// ロード処理
	FILE *pFile;
	if (nullptr == (pFile = fopen("data/ranking.txt", "r")))	// ファイルを開く(読み込みモード)
	{
		printf("ファイルが開けませんでした\n");
		exit(EXIT_FAILURE);
	}

	else
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			fscanf(pFile, "%d", &m_nScore[nCntRanking]);
		}
	}
	fclose(pFile);

	//プレイデータの取得
	CPlayData *pPlayData = CManager::GetPlayData();

	//プレイデータに保存してある今回のスコアを変数に保存
	m_nScore[MAX_SCORE_DATA - 1] = pPlayData->GetScore();
	m_nNowScore = pPlayData->GetScore();

	//ソート
	for (int nCntRanking = 0; nCntRanking < MAX_SCORE_DATA; nCntRanking++)
	{
		for (int nCntRanking2 = 0; nCntRanking2 < MAX_SCORE_DATA - 1; nCntRanking2++)
		{
			// 昇順で並べる
			if ((m_nScore[nCntRanking2] < m_nScore[nCntRanking2 + 1] && m_nScore[nCntRanking2 + 1] != 0) || m_nScore[nCntRanking2] == 0)
			{

				//if ((m_nScore[nCntRanking2] > m_nScore[nCntRanking2 + 1] && m_nScore[nCntRanking2] == 0) || m_nScore[nCntRanking2] == 0)

				int nScore = m_nScore[nCntRanking2];
				m_nScore[nCntRanking2] = m_nScore[nCntRanking2 + 1];
				m_nScore[nCntRanking2 + 1] = nScore;
			}
		}
	}

	//スコアの設定
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		m_apScore[nCntRanking]->SetScore(m_nScore[nCntRanking]);
	}

	//セーブ処理
	if (nullptr == (pFile = fopen("data/ranking.txt", "w")))
	{
		printf("ファイルが開けませんでした\n");
		exit(EXIT_FAILURE);
	}

	else
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			fprintf(pFile, "%d\n", m_apScore[nCntRanking]->GetScore());
		}
	}

	fclose(pFile);

	// カラーの設定
	m_col.r = 255.0f;
	m_col.g = 0.0f;
	m_col.b = 0.0f;
	m_col.a = 255.0f;

	return S_OK;
}

//================================================
// 終了処理
//================================================
void CRanking::Uninit(void)
{
#ifdef _DEBUG
	if (m_bClear)
	{
		ClearZeroRank();
	}
#endif

	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		if (m_apScene2D[nCntRanking] != nullptr)
		{
			m_apScene2D[nCntRanking]->Uninit();
			m_apScene2D[nCntRanking] = nullptr;
		}
	}

	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		if (m_apScore[nCntRanking] != nullptr)
		{
			m_apScore[nCntRanking]->Uninit();
			m_apScore[nCntRanking] = nullptr;
		}
	}

	Release();
}

//================================================
// 更新処理
//================================================
void CRanking::Update(void)
{
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		//スコアの位置取得処理
		D3DXVECTOR3 posScore = m_apScore[nCntRanking]->GetPos();

		if (posScore.x > SCREEN_WIDTH / 2.0f)
		{
			if (nCntRanking > 0)
			{
				//スコアの位置取得処理
				D3DXVECTOR3 posScorePrev = m_apScore[nCntRanking - 1]->GetPos();
				if (posScorePrev.x <= SCREEN_WIDTH / 2.0f)
				{
					posScore.x += RANKING_MOVE_X;
				}
			}
			else
			{
				posScore.x += RANKING_MOVE_X;
			}
			if (posScore.x <= SCREEN_WIDTH / 2.0f)
			{
				posScore.x = SCREEN_WIDTH / 2.0f;
			}
			//位置設定
			m_apScore[nCntRanking]->SetScorePos(posScore);
		}
	}

	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		if (m_nNowScore != 0 && m_nScore[nCntRanking] == m_nNowScore)
		{
			//カラーを薄くする
			m_col.a -= 255;
			if (m_col.r == 255)
			{
				m_col.r = 0;
				m_col.g = 255;
				m_col.b = 0;
			}
			else if (m_col.g == 255)
			{
				m_col.r = 0;
				m_col.g = 0;
				m_col.b = 255;
			}
			else if (m_col.b == 255)
			{
				m_col.r = 255;
				m_col.g = 0;
				m_col.b = 0;
			}

			if (m_col.a < 0)
			{
				m_col.a = 255;
			}

			for (int nCntNumber = 0; nCntNumber < MAX_SCORE; nCntNumber++)
			{
				//ナンバーを取得してカラーを設定
				m_apScore[nCntRanking]->GetNumber(nCntNumber)->SetCol(m_col);
			}
			break;
		}
	}

#ifdef _DEBUG
	CInputkeyboard *pKey = CManager::GetKeyboard();
	if (pKey->GetTrigger(DIK_R))
	{
		m_bClear = true;
	}
#endif
}

//================================================
//描画処理
//================================================
void CRanking::Draw(void)
{

}

//================================================
//生成処理
//================================================
CRanking* CRanking::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンスの生成
	CRanking *pRanking = nullptr;
	if (pRanking == nullptr)
	{
		pRanking = new CRanking;
		if (pRanking != nullptr)
		{
			pRanking->Init(pos, size);
		}
	}
	return pRanking;
}

//================================================
// スコア0クリア処理(デバッグのみ)
//================================================
#ifdef _DEBUG
void CRanking::ClearZeroRank()
{
	// ファイル構造体
	FILE *pFile = nullptr;

	if (pFile == nullptr)
	{
		if (nullptr != (pFile = fopen("data/ranking.txt", "w")))	// ファイルを開く(書き出しモード)
		{
			printf("ファイルが開けませんでした\n");
		}

		else
		{
			for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
			{
				fprintf(pFile, "%d\n", 0);							// ファイルに0を書き込む
			}		
		}
		fclose(pFile);	// ファイルを閉じる
	}
}
#endif
