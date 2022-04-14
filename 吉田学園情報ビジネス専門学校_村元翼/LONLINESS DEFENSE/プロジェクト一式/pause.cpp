//---------------------------------------------------
// �|�[�Y�̏���
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
#include <assert.h>

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define PAUSE_INERVAL (100.0f)
#define PAUSE_BG_ALPHA (0.8f)
#define SELECT_HEIGHT (300.0f)
#define SELECT_SIZE (D3DXVECTOR3(350.0f,60.0f,0.0f))
#define CURSOR_SIZE (D3DXVECTOR3(50.0f, 100.0f, 0.0f))

//--------------------------
// �ÓI�����o�ϐ��̏�����
//----------------------------
CBg *CPause::m_pBg = nullptr;

//--------------------------
// �R���X�g���N�^
//----------------------------
CPause::CPause(OBJTYPE nPriority) :CScene(nPriority)
{
	// �����o�ϐ��̏�����
	memset(m_pPolygon, 0, sizeof(m_pPolygon));
	m_pCursor = nullptr;
	m_bNextMode = false;
	m_bUninit = false;
	m_nPauseType = 0;
	m_fAlpha = 0.0f;
}

//--------------------------
// �f�X�g���N�^
//----------------------------
CPause::~CPause()
{

}

//--------------------------
// ������
//----------------------------
HRESULT CPause::Init(void)
{
	// �|�[�Y�w�i�̐����ƃJ���[�̐ݒ�
	m_pBg = CBg::Create(false, CTexture::MapFrame, CScene::OBJTYPE_PAUSE);
	m_pBg->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, PAUSE_BG_ALPHA));

	// �I�����̃|���S������
	int nType = 0;
	for (int nCnt = 0; nCnt < SELECT_MAX; nCnt++)
	{
		if (m_pPolygon[nCnt] == nullptr)
		{
			switch (nCnt)
			{
			case SELECT_RETURNGAME:
				nType = CTexture::GameBack;
				break;

			case SELECT_RETRY:
				nType = CTexture::Retry;
				break;

			case SELECT_RETURNTITLE:
				nType = CTexture::TitleBack;
				break;

			default:
				assert(nType <= -1 || nType > CTexture::Max);
				break;
			}

			// �I�����̐���
			m_pPolygon[nCnt] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SELECT_HEIGHT + (PAUSE_INERVAL * nCnt), 0.0f), SELECT_SIZE, (CTexture::Type)nType, CScene::OBJTYPE_PAUSE);
		}
	}

	// �J�[�\���̃|���S������
	if (m_pCursor == nullptr)
	{
		m_pCursor = CScene2D::Create(m_pos, CURSOR_SIZE, CTexture::Cursol, CScene::OBJTYPE_PAUSE);
	}

	return S_OK;
}

//--------------------------
// �I��
//----------------------------
void CPause::Uninit(void)
{
	for (int nCnt = 0; nCnt < SELECT_MAX; nCnt++)
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

	// �|�[�Y�w�i�̔j��
	if (m_pBg != nullptr)
	{
		m_pBg->Uninit();
		delete m_pBg;
		m_pBg = nullptr;
	}

	CManager::SetPause(false,false);	// �|�[�Y�̏�Ԃ�false�ɂ���
	Release();							// �I�u�W�F�N�g�̔j��
}

//--------------------------
// �X�V
//--------------------------
void CPause::Update(void)
{
	// �Q�[���p�b�h�̎擾
	CXInput *pXInput = CManager::GetXInput();
	CInputkeyboard *pKey = CManager::GetKeyboard();

	// ��ɍs��
	if (pKey->GetTrigger(DIK_W) || pXInput->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP))
	{
		// �|�[�Y�̃^�C�v�����炷
		m_nPauseType--;
		if (m_nPauseType < 0)
		{
			m_nPauseType = SELECT_MAX - 1;
		}
	}

	// ���ɍs��
	if (pKey->GetTrigger(DIK_S) || pXInput->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN))
	{
		// �|�[�Y�̃^�C�v�����炷
		m_nPauseType++;
		if (m_nPauseType >= SELECT_MAX)
		{
			m_nPauseType = 0;
		}
	}

	// �J�[�\���̈ʒu��ς���
	if (m_pCursor != nullptr)
	{
		switch (m_nPauseType)
		{
		case SELECT_RETURNGAME:
			m_pCursor->SetPos(D3DXVECTOR3(m_pPolygon[0]->GetPos().x - m_pPolygon[0]->GetScale().x, m_pPolygon[0]->GetPos().y, 0.0f), m_pCursor->GetScale());
			break;

		case SELECT_RETRY:
			m_pCursor->SetPos(D3DXVECTOR3(m_pPolygon[1]->GetPos().x - m_pPolygon[1]->GetScale().x, m_pPolygon[1]->GetPos().y, 0.0f), m_pCursor->GetScale());
			break;

		case SELECT_RETURNTITLE:
			m_pCursor->SetPos(D3DXVECTOR3(m_pPolygon[2]->GetPos().x - m_pPolygon[2]->GetScale().x, m_pPolygon[2]->GetPos().y, 0.0f), m_pCursor->GetScale());
			break;

		}
	}

	// �I�������肷��
	if ((pKey->GetTrigger(DIK_RETURN) || pXInput->GetButtonTrigger(XINPUT_GAMEPAD_A)) && !m_bNextMode)
	{
		switch (m_nPauseType)
		{
		case SELECT_RETURNGAME:	//�Q�[���ɖ߂�
			CManager::SetPause(false,false);
			break;
		case SELECT_RETRY:	//���g���C
			CFade::SetFade(CManager::MODE_GAME);
			break;
		case SELECT_RETURNTITLE:	//�^�C�g�����
			CFade::SetFade(CManager::MODE_TITLE);
			break;
		}
		m_bNextMode = true;
	}

	//---------------------------------------------------------------//
	// Uninit���Ă΂���Scene�ł̍X�V���~�܂邩����̂ݒʂ�d�g�� //
	//---------------------------------------------------------------//
	//�������������������������������������������������������������� //
	// �|�[�Y��Ԃ�false�Ȃ�
	if (!CManager::GetPause())
	{
		m_bUninit = true;	// 
	}

	if (m_bUninit)
	{
		Uninit();
	}

}

//--------------------------
// �`��
//----------------------------
void CPause::Draw(void)
{
	
}

//---------------------------------------------------------------
// �C���X�^���X��������
//---------------------------------------------------------------
CPause *CPause::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CPause *pPause = nullptr;
	if (pPause == nullptr)
	{
		pPause = new CPause(OBJTYPE_PAUSE);	// �������m��
		if (pPause != nullptr)
		{
			pPause->m_pos = pos;			// �ʒu
			pPause->Init();					// ����������
		}
	}

	return pPause;
}
