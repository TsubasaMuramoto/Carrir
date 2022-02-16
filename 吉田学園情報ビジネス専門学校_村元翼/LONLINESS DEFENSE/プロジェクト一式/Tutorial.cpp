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
//#include "sound.h"

//--------------------------------------------
//�R���X�g���N�^
//--------------------------------------------
CTutorial::CTutorial()
{
	memset(m_pTutorial, 0, sizeof(m_pTutorial));

	m_bNextMode = false;
}
//--------------------------------------------
//�f�X�g���N�^
//--------------------------------------------
CTutorial::~CTutorial()
{

}

//--------------------------------------------
//������
//--------------------------------------------
HRESULT CTutorial::Init(void)
{
	CBg::Create(false, CTexture::Bg, CScene::OBJTYPE_BG);	//�w�i

	m_pTutorial[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 350.0f, 0.0f), D3DXVECTOR3(1000.0f, 600.0f, 0.0f), CTexture::Tutorial01, CScene::OBJTYPE_BG);
	//CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 500.0f, 0.0f), D3DXVECTOR3(600.0f, 200.0f, 0.0f), CTexture::Tutorial02, CScene::OBJTYPE_BG);

	return S_OK;
}
//--------------------------------------------
//�I��
//--------------------------------------------
void CTutorial::Uninit(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pTutorial[nCnt]->Uninit();
		delete m_pTutorial[nCnt];
		m_pTutorial[nCnt] = nullptr;
	}
	//CManager::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_TITLE);
}
//--------------------------------------------
//�X�V
//--------------------------------------------
void CTutorial::Update(void)
{
	CInputkeyboard *pKey = CManager::GetKeyboard();
	CXInput *pGamePad = CManager::GetXInput();

	//if (m_bNextMode == false)
	//{
	//	if (pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP) == true)
	//	{
	//		m_nSelectType--;
	//		if (m_nSelectType < 0)
	//		{
	//			m_nSelectType = OPERATION;
	//		}

	//		CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_SELECT);
	//	}

	//	else if (pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN) == true)
	//	{
	//		m_nSelectType++;
	//		if (m_nSelectType >= MAX)
	//		{
	//			m_nSelectType = GAME_START;
	//		}

	//		CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_SELECT);

	//	}

	//}

	//switch (m_nSelectType)
	//{
	//case GAME_START:
	//	m_Cursol->SetPos(D3DXVECTOR3(m_Polygon[1]->GetPos().x - m_Polygon[1]->GetScale().x - 20.0f, m_Polygon[1]->GetPos().y, 0.0f));
	//	break;
	//case OPERATION:
	//	m_Cursol->SetPos(D3DXVECTOR3(m_Polygon[2]->GetPos().x - m_Polygon[2]->GetScale().x - 20.0f, m_Polygon[2]->GetPos().y, 0.0f));
	//	break;
	//}

	////A�{�^����������
	//if (pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_A) == true && m_bNextMode == false)
	//{
	//	CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_ENTER);

	//	if (m_bOpra == false)
	//	{
	//		switch (m_nSelectType)
	//		{
	//		case GAME_START:
	//			//�Q�[�����[�h�֍s��
	//			CFade::SetFade(CManager::MODE_GAME);
	//			////���ȏ�ʂ�Ȃ��悤�ɂ���
	//			m_bNextMode = true;

	//			break;
	//		case OPERATION:
	//			m_bOpra = true;
	//			m_Polygon[3] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CTexture::FADE);	//�`���[�g���A��
	//			m_Polygon[4] = CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 3.0f, 0.0f), CTexture::Operation01);	//�`���[�g���A��
	//			m_Polygon[3]->SetCol(D3DXCOLOR(1.0, 1.0, 1.0, 0.5));
	//			break;
	//		}
	//	}
	//	//�`���[�g���A����ʐ������o����
	//	else if (m_bOpra == true)
	//	{
	//		//A��B�{�^����������
	//		if (pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_A) == true)
	//		{
	//			if (m_Polygon[3] != NULL)
	//			{
	//				m_Polygon[3]->Uninit();
	//				m_Polygon[3] = NULL;
	//				m_bOpra = false;
	//			}
	//			if (m_Polygon[4] != NULL)
	//			{
	//				m_Polygon[4]->Uninit();
	//				m_Polygon[4] = NULL;
	//			}


	//		}
	//	}
	//}

	// ENTER������
	if ((pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_START) || pKey->GetTrigger(DIK_RETURN) == true) && m_bNextMode == false && m_pTutorial[1] != nullptr)
	{
		CFade::SetFade(CManager::MODE_GAME);			// �Q�[�����[�h��
		m_bNextMode = true;								// ENTER�A�Ŗh�~
	}

	else if((pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_START) || pKey->GetTrigger(DIK_RETURN) == true) && m_pTutorial[1] == nullptr)
	{
		m_pTutorial[0]->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		m_pTutorial[1] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 350.0f, 0.0f), D3DXVECTOR3(1000.0f, 600.0f, 0.0f), CTexture::Tutorial02, CScene::OBJTYPE_BG);
	}
}
//--------------------------------------------
//�`��
//--------------------------------------------
void CTutorial::Draw(void)
{

}

