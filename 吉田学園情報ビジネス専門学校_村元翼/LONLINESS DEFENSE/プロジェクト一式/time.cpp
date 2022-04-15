//---------------------------------------------------------------
// �^�C���̍쐬
// Author : ������
//---------------------------------------------------------------
#include "main.h" 
#include "manager.h"
#include "number.h"
#include "time.h"
#include "fade.h"
#include "sound.h"
#include <time.h>

//---------------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------------
CTime::CTime(OBJTYPE nPriority) : CScene(nPriority)
{
	// �����o�ϐ��̏�����
	m_bNextMode = false;
	m_nFrame = 0;				// �t���[��������
	m_nTime = TIME_LIMIT;		// �������Ԃ̐ݒ�
}

//---------------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------------
CTime::~CTime()
{
}

//---------------------------------------------------------------
// �^�C���̐���
//---------------------------------------------------------------
CTime *CTime::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �C���X�^���X����
	CTime *pTime = nullptr;

	if (pTime == nullptr)
	{
		pTime = new CTime;

		if (pTime != nullptr)
		{
			pTime->Init(pos, size);	// ������
		}
	}

	return pTime;
}

//---------------------------------------------------------------
// ������
//---------------------------------------------------------------
HRESULT CTime::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �|���S���̐���
	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		m_apNumber[nCntTime] = CNumber::Create(D3DXVECTOR3(pos.x + nCntTime * size.x, pos.y, pos.z), size);
		m_apNumber[nCntTime]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_nAll++;	// �^�C�������𑝂₷
	}
	return S_OK;
}

HRESULT CTime::Init(void)
{
	return 0;
}

//---------------------------------------------------------------
// �I��
//---------------------------------------------------------------
void CTime::Uninit()
{
	m_nAll--;	// �^�C�����������炷
	Release();	// �C���X�^���X�j��
}

//---------------------------------------------------------------
// �X�V
//---------------------------------------------------------------
void CTime::Update()
{
	m_nFrame++;// �t���[������

	// 60�t���[���������
	if (m_nFrame >= TIME_FRAME)
	{
		m_nFrame = 0;	// �t���[��������
		m_nTime --;	// �^�C����1�b���炷
	}

	// 20�b�ȉ��ɂȂ�����ԐF�ɂ���
	if (m_nTime <= TIME_REDZONE)
	{
		for (int nCnt = 0; nCnt < m_nAll; nCnt++)
		{
			m_apNumber[nCnt]->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));	// �J���[�̐ݒ�
		}
	}

	// 0�b���Ⴍ�Ȃ�Ȃ��悤�ɂ���
	if (m_nTime <= 0)
	{
		if (!m_bNextMode)	// ���U���g�ڍs
		{
			m_bNextMode = true;
			CFade::SetFade(CManager::MODE_RESULT);
		}
		m_nTime = 0;
	}

	SetTime();	// �`��̐ݒ�
}

//---------------------------------------------------------------
// �`��
//---------------------------------------------------------------
void CTime::Draw()
{
	for (int nCntTime = 0; nCntTime < m_nAll; nCntTime++)
	{
		if (m_apNumber[nCntTime] != nullptr)
		{
			m_apNumber[nCntTime]->Draw();
		}
	}
}

//---------------------------------------------------------------
// �`��̐ݒ�
//---------------------------------------------------------------
void CTime::SetTime()
{
	// �i���o�[�̌����̌v�Z����
	for (int nCnt = 0, nDecrement = 1; nCnt < m_nAll; nCnt++, nDecrement *= 10)
	{
		m_apNumber[nCnt]->SetNumber(m_nTime % ((int)pow(10, m_nAll) / nDecrement) / ((int)pow(10, m_nAll - 1) / nDecrement));
	}
}