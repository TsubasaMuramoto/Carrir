//--------------------------------------
// �}�l�[�W���[�̏���
//--------------------------------------
#include "title.h"
#include "bg.h"
#include "texture.h"
#include "manager.h"
#include "keyboard.h"
#include "fade.h"
#include "XInput.h"
#include "sound.h"

//--------------------------------------
// �}�N����`
//--------------------------------------
#define BLINK_INTERVAL (60)
#define BLINK_SPEED (5)

//--------------------------------------------
// �R���X�g���N�^
//--------------------------------------------
CTitle::CTitle()
{
	// �����o�ϐ��̏�����
	memset(m_pTitle, 0, sizeof(m_pTitle));
	m_bNextMode = false;
	m_nFrame = 0;
	m_nMultiFrame = 1;
}

//--------------------------------------------
// �f�X�g���N�^
//--------------------------------------------
CTitle::~CTitle()
{

}

//--------------------------------------------
// ������
//--------------------------------------------
HRESULT CTitle::Init(void)
{
	CBg::Create(false ,CTexture::Target,CScene::OBJTYPE_BG);	// �w�i

	m_pTitle[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f, 0.0f), D3DXVECTOR3(1000.0f, 300.0f, 0.0f), CTexture::Title, CScene::OBJTYPE_BG);
	m_pTitle[1] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 500.0f, 0.0f), D3DXVECTOR3(600.0f, 200.0f, 0.0f), CTexture::PressEnter,CScene::OBJTYPE_BG);

	return S_OK;
}

//--------------------------------------------
// �I��
//--------------------------------------------
void CTitle::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_TITLE_POLYGON; nCnt++)
	{
		if (m_pTitle[nCnt] != nullptr)
		{
			m_pTitle[nCnt]->Uninit();
			delete m_pTitle[nCnt];
			m_pTitle[nCnt] = nullptr;
		}
	}
}

//--------------------------------------------
// �X�V
//--------------------------------------------
void CTitle::Update(void)
{
	// �I�u�W�F�N�g�擾
	CInputkeyboard *pKey = CManager::GetKeyboard();
	CXInput *pGamePad = CManager::GetXInput();

	// press start�_�ŏ���
	if (m_pTitle[1] != nullptr)
	{
		m_nFrame++;
		if (m_nFrame > (BLINK_INTERVAL / 2) / m_nMultiFrame && m_nFrame <= BLINK_INTERVAL / m_nMultiFrame)
		{
			m_pTitle[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}

		else if (m_nFrame > BLINK_INTERVAL / m_nMultiFrame)
		{
			m_pTitle[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_nFrame = 0;
		}
	}

	// ENTER������
	if (pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_START) || pKey->GetTrigger(DIK_RETURN) && !m_bNextMode)
	{
		// �I�u�W�F�N�g�擾
		CSound *pSound = CManager::GetSound();

		m_nMultiFrame = BLINK_SPEED;
		CFade::SetFade(CManager::MODE_TUTORIAL);		// �Q�[�����[�h��
		m_bNextMode = true;								// ENTER�A�Ŗh�~
	}
}

//--------------------------------------------
// �`��
//--------------------------------------------
void CTitle::Draw(void)
{

}

