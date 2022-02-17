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
	m_bNextMode = false;
	m_bUninit = false;
	m_nPauseType = 0;
	m_fAlpha = 0.0f;
	m_pCursor = nullptr;
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
	m_pBg->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f));

	// �I�����̃|���S������
	for (int nCnt = 0; nCnt < MAX_PAUSE; nCnt++)
	{
		if (m_pPolygon == nullptr)
		{
			m_pPolygon[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SELECT_HEIGHT + (PAUSE_INERVAL * 0), 0.0f), SELECT_SIZE, CTexture::GameBack, CScene::OBJTYPE_PAUSE);
			m_pPolygon[1] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SELECT_HEIGHT + (PAUSE_INERVAL * 1), 0.0f), SELECT_SIZE, CTexture::Retry, CScene::OBJTYPE_PAUSE);
			m_pPolygon[2] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SELECT_HEIGHT + (PAUSE_INERVAL * 2), 0.0f), SELECT_SIZE, CTexture::TitleBack, CScene::OBJTYPE_PAUSE);
		}
	}

	// �J�[�\���̃|���S������
	if (m_pCursor == nullptr)
	{
		m_pCursor = CScene2D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + (PAUSE_INERVAL * 0), 0.0f), D3DXVECTOR3(50.0f, 100.0f, 0.0f), CTexture::Cursol, CScene::OBJTYPE_UI);
	}

	return S_OK;
}

//--------------------------
// �I��
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
	if (pKey->GetTrigger(DIK_W) == true ||
		pXInput->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP) == true)
	{
		// �|�[�Y�̃^�C�v�����炷
		m_nPauseType--;
		if (m_nPauseType < 0)
		{
			m_nPauseType = MAX_PAUSE - 1;
		}
	}

	// ���ɍs��
	if (pKey->GetTrigger(DIK_S) == true ||
		pXInput->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN) == true)
	{
		// �|�[�Y�̃^�C�v�����炷
		m_nPauseType++;
		if (m_nPauseType >= MAX_PAUSE)
		{
			m_nPauseType = 0;
		}
	}

	// �J�[�\���̈ʒu��ς���
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

	// �I�������肷��
	if ((pKey->GetTrigger(DIK_RETURN) == true || pXInput->GetButtonTrigger(XINPUT_GAMEPAD_A) == true) && m_bNextMode == false)
	{
		switch (m_nPauseType)
		{
		case 0:	//�Q�[���ɖ߂�
			CManager::SetPause(false,false);
			break;
		case 1:	//���g���C
			CFade::SetFade(CManager::MODE_GAME);
			break;
		case 2:	//�^�C�g�����
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
			pPause->m_pos = pos;
			pPause->Init();
		}
	}

	return pPause;
}
