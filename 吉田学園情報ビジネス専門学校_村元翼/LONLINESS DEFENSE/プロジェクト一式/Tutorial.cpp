//--------------------------------------
// �`���[�g���A���̏���
//--------------------------------------
#include "Tutorial.h"
#include "bg.h"
#include "texture.h"
#include "manager.h"
#include "keyboard.h"
#include "fade.h"
#include "polygon.h"
#include "XInput.h"

//--------------------------------------------
// �R���X�g���N�^
//--------------------------------------------
CTutorial::CTutorial()
{
	// �����o�ϐ��̏�����
	memset(m_pTutorial, 0, sizeof(m_pTutorial));
	m_bNextMode = false;
}
//--------------------------------------------
// �f�X�g���N�^
//--------------------------------------------
CTutorial::~CTutorial()
{

}

//--------------------------------------------
// ������
//--------------------------------------------
HRESULT CTutorial::Init(void)
{
	CBg::Create(false, CTexture::Bg, CScene::OBJTYPE_BG);	// �w�i

	// �`���[�g���A���y�[�W�̂P����
	m_pTutorial[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 350.0f, 0.0f), D3DXVECTOR3(1000.0f, 600.0f, 0.0f), CTexture::Tutorial01, CScene::OBJTYPE_BG);

	return S_OK;
}
//--------------------------------------------
// �I��
//--------------------------------------------
void CTutorial::Uninit(void)
{
	// �����o�ϐ��̏I��
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pTutorial[nCnt]->Uninit();
		delete m_pTutorial[nCnt];
		m_pTutorial[nCnt] = nullptr;
	}
}
//--------------------------------------------
// �X�V
//--------------------------------------------
void CTutorial::Update(void)
{
	// ���̓f�o�C�X�̎擾
	CInputkeyboard *pKey = CManager::GetKeyboard();
	CXInput *pGamePad = CManager::GetXInput();

	// Enter�Ń��[�h�ύX
	if ((pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_START) || pKey->GetTrigger(DIK_RETURN) == true) && m_bNextMode == false && m_pTutorial[1] != nullptr)
	{
		CFade::SetFade(CManager::MODE_GAME);			// �Q�[�����[�h��
		m_bNextMode = true;								// ENTER�A�Ŗh�~
	}

	// �y�[�W��ς���
	else if((pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_START) || pKey->GetTrigger(DIK_RETURN) == true) && m_pTutorial[1] == nullptr)
	{
		m_pTutorial[0]->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		m_pTutorial[1] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 350.0f, 0.0f), D3DXVECTOR3(1000.0f, 600.0f, 0.0f), CTexture::Tutorial02, CScene::OBJTYPE_BG);
	}
}
//--------------------------------------------
// �`��
//--------------------------------------------
void CTutorial::Draw(void)
{

}

