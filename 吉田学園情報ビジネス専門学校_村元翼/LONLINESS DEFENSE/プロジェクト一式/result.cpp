//--------------------------------------
// ���U���g��ʂ̏���
//--------------------------------------
#include "result.h"
#include "manager.h"
#include "keyboard.h"
#include "fade.h"
#include "ranking.h"
#include "XInput.h"
#include "sound.h"

//--------------------------------------------
// �R���X�g���N�^
//--------------------------------------------
CResult::CResult()
{
	m_bNextMode = false;
}
//--------------------------------------------
// �f�X�g���N�^
//--------------------------------------------
CResult::~CResult()
{

}

//--------------------------------------------
// ������
//--------------------------------------------
HRESULT CResult::Init(void)
{
	//�����L���O�̐���
	m_pRanking = CRanking::Create
	(
		D3DXVECTOR3(500.0f + RANKING_POLYGON_WIDTH * MAX_SCORE, RESULT_RANKING_POSY, 0.0f),
		D3DXVECTOR3(RANKING_POLYGON_WIDTH, RANKING_POLYGON_HEIGHT, 0.0f)
	);																																					//m_pBg->SetCol(D3DXCOLOR(0.0, 0.0, 1.0, 1.0));

	return S_OK;
}
//--------------------------------------------
// �I��
//--------------------------------------------
void CResult::Uninit(void)
{
	if (m_pRanking != nullptr)
	{
		m_pRanking->Uninit();
		m_pRanking = nullptr;
	}
}
//--------------------------------------------
// �X�V
//--------------------------------------------
void CResult::Update(void)
{
	// ���̓f�o�C�X�̎擾
	CInputkeyboard *pKey = CManager::GetKeyboard();
	CXInput *pGamePad = CManager::GetXInput();	

	// ENTER������
	if (pGamePad->GetButtonTrigger(XINPUT_GAMEPAD_START) || pKey->GetTrigger(DIK_RETURN) && !m_bNextMode)
	{
		CFade::SetFade(CManager::MODE_TITLE);			// �Q�[�����[�h��
		m_bNextMode = true;								// ENTER�A�Ŗh�~
	}
}
//--------------------------------------------
// �`��
//--------------------------------------------
void CResult::Draw(void)
{

}

