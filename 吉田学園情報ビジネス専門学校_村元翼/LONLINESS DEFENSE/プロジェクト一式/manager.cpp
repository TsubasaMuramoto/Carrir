//--------------------------------------
// �}�l�[�W���[�̏���
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
//�ÓI�����o�ϐ��錾
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
CManager::MODE	CManager::m_Mode = MODE_GAME;	// �f�o�b�O���[�h���ɒʂ�
#endif

#ifndef _DEBUG
CManager::MODE	CManager::m_Mode = MODE_TITLE;	// �����[�X���[�h���ɒʂ�
#endif

//--------------------------------------------
//�R���X�g���N�^
//--------------------------------------------
CManager::CManager()
{
}

//--------------------------------------------
//�f�X�g���N�^
//--------------------------------------------
CManager::~CManager()
{
}

//--------------------------------------------
// ������
//--------------------------------------------
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// �T�E���h�̐���
	if(m_pSound == nullptr)
	{ 
		m_pSound = new CSound;

		if (m_pSound != nullptr)
		{
			m_pSound->Init(hWnd);
		}
	}

	//�v���C�f�[�^�N���X�̐���
	if (m_pPlayData == nullptr)
	{
		m_pPlayData = new CPlayData;

		if (m_pPlayData != nullptr)
		{
			m_pPlayData->Init();
		}
	}

	// �����_���[�̐���
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

	// �e�N�X�`���̐����Ə�����
	if (m_pTexture == nullptr)
	{
		m_pTexture = new CTexture;

		if (m_pTexture != nullptr)
		{
			m_pTexture->Init();
		}
	}

	// �L�[�{�[�h�̐����Ə�����
	if (m_pKeyboard == nullptr)
	{
		m_pKeyboard = new CInputkeyboard;

		if (m_pKeyboard != nullptr)
		{
			m_pKeyboard->Init(hInstance, hWnd);
		}
	}

	// �}�E�X�̐����Ə�����
	if (m_pMouse == nullptr)
	{
		m_pMouse = new CMouse;

		if (m_pMouse != nullptr)
		{
			m_pMouse->Init(hInstance, hWnd);
		}
	}

	// Xinput�̐���
	if (m_pXInput == nullptr)
	{
		m_pXInput = new CXInput;
	}

	// ���[�h�̐ݒ�
	SetMode(m_Mode);

	// �t�F�[�h�̐���
	if (m_pFade == nullptr)
	{
		m_pFade = CFade::Create(CTexture::Gauge, m_Mode);
	}
	
	//-----------------------------------------
	// �e��I�u�W�F�N�g�̐���
	//-----------------------------------------
	return S_OK;
}
//--------------------------------------------
// �I��
//--------------------------------------------
void CManager::Uninit(void)
{
	// �I�u�W�F�N�g�̔j��
	CScene::ReleaseAll();

	// Xinput�̔j��
	if (m_pXInput != nullptr)
	{
		delete m_pXInput;
		m_pXInput = nullptr;
	}

	// �}�E�X�̔j��
	if (m_pMouse != nullptr)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = nullptr;
	}

	// �L�[�{�[�h�̔j��
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	// �e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Uninit();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	// �t�F�[�h�̔j��
	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}

	// �����_���[�̔j��
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	// �v���C�f�[�^�̔j��
	if (m_pPlayData != nullptr)
	{
		m_pPlayData->Uninit();
		delete m_pPlayData;
		m_pPlayData = nullptr;
	}

	// �v���C�f�[�^�̔j��
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}
}
//--------------------------------------------
// �X�V
//--------------------------------------------
void CManager::Update(void)
{
	// �����_���[�̍X�V
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}

	// �L�[�{�[�h�̍X�V
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Update();
	}

	// �}�E�X�̍X�V
	if (m_pMouse != nullptr)
	{
		m_pMouse->Update();
	}


	// �Q�[���p�b�h�̍X�V
	if (m_pXInput != nullptr)
	{
		m_pXInput->UpdateGamepad();
	}


	// ���[�h���̍X�V
	switch (m_Mode)
	{
	case MODE_TITLE:		// �^�C�g�����
		if (m_pTitle != nullptr)
		{
			m_pTitle->Update();
		}
		break;

	case MODE_TUTORIAL:		// �`���[�g���A�����
		if (m_pTutorial != nullptr)
		{
			m_pTutorial->Update();
		}
		break;

	case MODE_GAME:			// �Q�[�����
		if (m_pGame != nullptr)
		{
			m_pGame->Update();

			// �|�[�Y�؂�ւ�(P������)
			if (GetKeyboard()->GetTrigger(DIK_P)|| GetXInput()->GetButtonTrigger(XINPUT_GAMEPAD_START))
			{
				m_bStop = !m_bStop;			// �X�g�b�v��؂�ւ���

				m_bPause = !m_bPause;		// �|�[�Y��؂�ւ���
			}

			// �X�g�b�v���
			if (m_bStop)
			{
				// �R���g���[���[�̃o�C�u���[�V�����Ǝ~�߂�
				m_pXInput->SetVibration(0, 0);

				// �|�[�Y�̐���
				if (m_pPause == nullptr)
				{
					m_pPause = CPause::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
			}

			else
			{
				// �|�[�Y��NULL�ɂ���
				if (m_pPause != nullptr)
				{
					// delete��Scene�ōs��
					m_pPause->Uninit();
					m_pPause = nullptr;
				}
			}

		}
		break;

	case MODE_RESULT:		//���U���g���
		if (m_pResult != nullptr)
		{
			m_pResult->Update();
		}
		break;
	}
}
//--------------------------------------------
// �`��
//--------------------------------------------
void CManager::Draw(void)
{
	// �����_���[�̕`��
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Draw();
	}

	// ���[�h���̕`��
	switch (m_Mode)
	{
	case MODE_TITLE:		// �^�C�g�����
		if (m_pTitle != nullptr)
		{
			m_pTitle->Draw();
		}
		break;

	case MODE_TUTORIAL:		// �`���[�g���A�����
		if (m_pTutorial != nullptr)
		{
			m_pTutorial->Draw();
		}
		break;

	case MODE_GAME:			// �Q�[�����
		if (m_pGame != nullptr)
		{
			m_pGame->Draw();
		}
		break;

	case MODE_RESULT:		// ���U���g���
		if (m_pResult != nullptr)
		{
			m_pResult->Draw();
		}
		break;
	}
}

//-----------------------------------------------------------------------------
// ���[�h�̏���
//-----------------------------------------------------------------------------
void CManager::SetMode(MODE mode)
{
	//m_bEnd = false;

	// ���݂̃��[�h��j��
	switch (m_Mode)
	{
	case MODE_TITLE:		//�^�C�g�����
		if (m_pTitle != nullptr)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = nullptr;
		}
		break;

	case MODE_TUTORIAL:		// �`���[�g���A�����
		if (m_pTutorial != nullptr)
		{
			m_pTutorial->Uninit();
			delete m_pTutorial;
			m_pTutorial = nullptr;
		}
		break;

	case MODE_GAME:			// �Q�[�����
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

	case MODE_RESULT:		//���U���g���
		if (m_pResult != nullptr)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = nullptr;
		}
		break;
	}

	//���݂̃��[�h�Ő��������I�u�W�F�N�g�̍폜
	CScene::ReleaseAll();

	// ���Ɉڍs���郂�[�h�̐���
	switch (mode)
	{
	case MODE_TITLE:		//�^�C�g�����
		if (m_pTitle == nullptr)
		{
			m_pTitle = new CTitle;
			m_pTitle->Init();
		}
		break;

	case MODE_TUTORIAL:		// �`���[�g���A�����
		if (m_pTutorial == nullptr)
		{
			m_pTutorial = new CTutorial;
			m_pTutorial->Init();
		}
		break;

	case MODE_GAME:			//�Q�[�����
		if (m_pGame == nullptr)
		{
			m_bPause = false;
			m_bStop = false;

			m_pGame = new CGame;
			m_pGame->Init();
		}
		break;
	case MODE_RESULT:		//���U���g���
		if (m_pResult == nullptr)
		{
			m_pResult = new CResult;
			m_pResult->Init();
		}
		break;
	}

	//���̃��[�h�����݂̃��[�h�ɏ㏑��
	m_Mode = mode;
}