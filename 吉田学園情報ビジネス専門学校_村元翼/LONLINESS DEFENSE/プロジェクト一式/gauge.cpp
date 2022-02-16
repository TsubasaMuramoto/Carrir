//============================================================
// �Q�[�W�̏���
//============================================================
#include "main.h" 
#include "manager.h"
#include "renderer.h"
#include "gauge.h"
#include "fade.h"

//============================================================
// �ÓI�����o�ϐ��̏�����
//============================================================
D3DXVECTOR3 CGauge::m_Scale = {};

//============================================================
// �R���X�g���N�^
//============================================================
CGauge::CGauge(OBJTYPE nPriority) : CScene2D(nPriority)
{
	m_bNextMode = false;
	m_fScaleSpeed = 0.1f;
}

//============================================================
// �f�X�g���N�^
//============================================================
CGauge::~CGauge()
{

}

//============================================================
// �Q�[�W�̐���
//============================================================
CGauge *CGauge::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	// �C���X�^���X����
	CGauge *pGauge = new CGauge;

	if (pGauge != nullptr)
	{
		pGauge->m_pos = pos;
		pGauge->m_Scale = scale;
		pGauge->Init(pGauge->m_pos, pGauge->m_Scale);
	}

	return pGauge;
}

//============================================================
// ������
//============================================================
HRESULT CGauge::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CScene2D::BindTexture(CTexture::Gauge);
	CScene2D::Init();
	CScene2D::SetScalePos(pos, scale);
	CScene2D::SetCol(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

	return S_OK;
}

HRESULT CGauge::Init(void)
{
	return 0;
}

//============================================================
// �I��
//============================================================
void CGauge::Uninit()
{
	CScene2D::Uninit();
}

//============================================================
// �X�V
//============================================================
void CGauge::Update()
{
	CScene2D::Update();
	CScene2D::SetScalePos(m_pos, m_Scale);
	//m_Scale.x += m_fScaleSpeed;//�Q�[�W�̏㏸

	// �Q�[�W�̐U��؂�h�~
	if (m_Scale.x <= 0)
	{
		m_Scale.x = 0.0f;
	}

	// �Q�[�W���Ȃ��Ȃ�
	if (m_Scale.x <= 0.0f && m_bNextMode == false)
	{
		m_Scale.x = 0.0f;			
		CFade::SetFade(CManager::MODE_RESULT);	// ���U���g�֍s��
		m_bNextMode = true;						// ���݂̂��̏�������ʂ�
	}

	if (m_Scale.x < MAX_GAUGE_WIDTH / 2)
	{
		CScene2D::SetCol(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	}
	if (m_Scale.x < MAX_GAUGE_WIDTH / 4)
	{
		CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}
}

//============================================================
// �`��
//============================================================
void CGauge::Draw()
{
	CScene2D::Draw();
}

//============================================================
// �Q�[�W�̐ݒ�
//============================================================
void CGauge::SetGauge(float Set)
{
	if (m_Scale.x <= MAX_GAUGE_WIDTH)
	{
		m_Scale.x += Set;
	}
}