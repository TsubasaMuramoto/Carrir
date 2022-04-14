//================================================
//�����L���O����
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
//�ÓI�����o�ϐ��錾
//================================================
CScore *CRanking::m_apScore[MAX_RANKING] = {};

//================================================
//�f�t�H���g�R���X�g���N�^
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
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CRanking::~CRanking()
{

}

//================================================
//����������
//================================================
HRESULT CRanking::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		//�X�R�A�̐���
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

		// �����N����
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

	// ���[�h����
	FILE *pFile;
	if (nullptr == (pFile = fopen("data/ranking.txt", "r")))	// �t�@�C�����J��(�ǂݍ��݃��[�h)
	{
		printf("�t�@�C�����J���܂���ł���\n");
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

	//�v���C�f�[�^�̎擾
	CPlayData *pPlayData = CManager::GetPlayData();

	//�v���C�f�[�^�ɕۑ����Ă��鍡��̃X�R�A��ϐ��ɕۑ�
	m_nScore[MAX_SCORE_DATA - 1] = pPlayData->GetScore();
	m_nNowScore = pPlayData->GetScore();

	//�\�[�g
	for (int nCntRanking = 0; nCntRanking < MAX_SCORE_DATA; nCntRanking++)
	{
		for (int nCntRanking2 = 0; nCntRanking2 < MAX_SCORE_DATA - 1; nCntRanking2++)
		{
			// �����ŕ��ׂ�
			if ((m_nScore[nCntRanking2] < m_nScore[nCntRanking2 + 1] && m_nScore[nCntRanking2 + 1] != 0) || m_nScore[nCntRanking2] == 0)
			{

				//if ((m_nScore[nCntRanking2] > m_nScore[nCntRanking2 + 1] && m_nScore[nCntRanking2] == 0) || m_nScore[nCntRanking2] == 0)

				int nScore = m_nScore[nCntRanking2];
				m_nScore[nCntRanking2] = m_nScore[nCntRanking2 + 1];
				m_nScore[nCntRanking2 + 1] = nScore;
			}
		}
	}

	//�X�R�A�̐ݒ�
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		m_apScore[nCntRanking]->SetScore(m_nScore[nCntRanking]);
	}

	//�Z�[�u����
	if (nullptr == (pFile = fopen("data/ranking.txt", "w")))
	{
		printf("�t�@�C�����J���܂���ł���\n");
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

	// �J���[�̐ݒ�
	m_col.r = 255.0f;
	m_col.g = 0.0f;
	m_col.b = 0.0f;
	m_col.a = 255.0f;

	return S_OK;
}

//================================================
// �I������
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
// �X�V����
//================================================
void CRanking::Update(void)
{
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		//�X�R�A�̈ʒu�擾����
		D3DXVECTOR3 posScore = m_apScore[nCntRanking]->GetPos();

		if (posScore.x > SCREEN_WIDTH / 2.0f)
		{
			if (nCntRanking > 0)
			{
				//�X�R�A�̈ʒu�擾����
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
			//�ʒu�ݒ�
			m_apScore[nCntRanking]->SetScorePos(posScore);
		}
	}

	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		if (m_nNowScore != 0 && m_nScore[nCntRanking] == m_nNowScore)
		{
			//�J���[�𔖂�����
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
				//�i���o�[���擾���ăJ���[��ݒ�
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
//�`�揈��
//================================================
void CRanking::Draw(void)
{

}

//================================================
//��������
//================================================
CRanking* CRanking::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X�̐���
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
// �X�R�A0�N���A����(�f�o�b�O�̂�)
//================================================
#ifdef _DEBUG
void CRanking::ClearZeroRank()
{
	// �t�@�C���\����
	FILE *pFile = nullptr;

	if (pFile == nullptr)
	{
		if (nullptr != (pFile = fopen("data/ranking.txt", "w")))	// �t�@�C�����J��(�����o�����[�h)
		{
			printf("�t�@�C�����J���܂���ł���\n");
		}

		else
		{
			for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
			{
				fprintf(pFile, "%d\n", 0);							// �t�@�C����0����������
			}		
		}
		fclose(pFile);	// �t�@�C�������
	}
}
#endif
