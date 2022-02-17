//-------------------------------------------------------------------
// �t�F�[�h�̏���
//-------------------------------------------------------------------
#include "fade.h"
#include "bg.h"
#include "texture.h"
#include "manager.h"
#include "scene2D.h"

//-------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------------------------------
CFade::FADE					CFade::m_fade = CFade::FADE_IN;
CManager::MODE				CFade::m_modeNext = CManager::MODE_TITLE;
float						CFade::m_colorAlpha = 1.0f;
CBg							*CFade::m_pBg = NULL;

//--------------------------------------------
// �R���X�g���N�^
//--------------------------------------------
CFade::CFade(OBJTYPE nPriority) :CScene(nPriority)
{
	
}

//--------------------------------------------
// �f�X�g���N�^
//--------------------------------------------
CFade::~CFade()
{

}

//---------------------------------------------------------------
// �C���X�^���X��������
//---------------------------------------------------------------
CFade *CFade::Create(CTexture::Type type, CManager::MODE modeNext)
{
	//�C���X�^���X����
	CFade *pFade = new CFade(OBJTYPE_FADE);

	if (pFade != NULL)
	{
		pFade->m_modeNext = modeNext;
		pFade->m_Type = type;
		pFade->Init();
	}
	return pFade;
}

//--------------------------------------------
// ������
//--------------------------------------------
HRESULT CFade::Init(void)
{
	// �w�i����
	m_pBg = CBg::Create(false,CFade::m_Type,CScene::OBJTYPE_FADE);

	return S_OK;
}

//--------------------------------------------
// �I��
//--------------------------------------------
void CFade::Uninit(void)
{
	Release();
}

//--------------------------------------------
// �X�V
//--------------------------------------------
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		m_pBg->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colorAlpha));

		// �t�F�[�h��ʂ�����
		if (m_fade == FADE_IN)
		{
			m_colorAlpha -= 0.05f;
			if (m_colorAlpha <= 0.0f)
			{
				m_colorAlpha = 0.0f;
				m_fade = FADE_NONE;
			}

		}
		// �t�F�[�h��ʂ��o��
		else if (m_fade == FADE_OUT)
		{
			m_colorAlpha += 0.01f;

			if (m_colorAlpha >= 1.0f)
			{
				m_colorAlpha = 1.0f;
				m_fade = FADE_IN;

				// ���[�h�̐ݒ�
				CManager::SetMode(m_modeNext);
			}
		}
	}
}

//--------------------------------------------
// �`��
//--------------------------------------------
void CFade::Draw(void)
{

}

//--------------------------------------------
// �t�F�[�h�̐ݒ菈��
//--------------------------------------------
void CFade::SetFade(CManager::MODE modeNext)
{
	m_fade = FADE_OUT;
	m_modeNext = modeNext;
	m_colorAlpha = 0.0f;
}

//--------------------------------------------
// �t�F�[�h�̎擾����
//--------------------------------------------
CFade::FADE CFade::GetFade(void)
{
	return m_fade;
}
