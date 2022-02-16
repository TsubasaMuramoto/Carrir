//---------------------------------------------------
// �w�i�̏���
//---------------------------------------------------
#include "bg.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "keyboard.h"
#include "player.h"
#include "game.h"

//--------------------------
// �ÓI�����o�ϐ�������
//----------------------------
const D3DXVECTOR2 CBg::m_SpreadRange_min =  D3DXVECTOR2(0.0f, 0.0f);
const D3DXVECTOR2 CBg::m_SpreadRange_max =  D3DXVECTOR2(SCREEN_WIDTH,SCREEN_HEIGHT);

//--------------------------
// �R���X�g���N�^
//----------------------------
CBg::CBg(OBJTYPE nPriority):CScene2D(nPriority)
{
	m_Tex = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bScroll = false;
	m_bCanScroll = false;
}

//--------------------------
// �f�X�g���N�^
//----------------------------
CBg::~CBg()
{

}

//--------------------------
// ������
//----------------------------
HRESULT CBg::Init()
{
	CScene2D::BindTexture(m_Type);
	CScene2D::Init();
	CScene2D::SetPos
	(
		D3DXVECTOR3(0.0f,0.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH,0.0f, 0.0f),
		D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f)
	);
	CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//--------------------------
// �I��
//----------------------------
void CBg::Uninit(void)
{
	CScene2D::Uninit();
}

//--------------------------
// �X�V
//----------------------------
void CBg::Update(void)
{
	CScene2D::Update();
	BgLimit();

	if (m_bCanScroll == true)
	{
		m_pos += CGame::GetScroll();				// ���ۂɃX�N���[��������
		m_Tex += CGame::GetScroll() * 0.001f;		// �w�i�X�s�[�h���擾&����
		CScene2D::SetTex(m_Tex.x, m_Tex.y);			// �e�N�X�`���X�V
	}	
}

//--------------------------
//�`��
//----------------------------
void CBg::Draw(void)
{
	CScene2D::Draw();
}

//---------------------------------------------------------------
//�C���X�^���X��������
//---------------------------------------------------------------
CBg *CBg::Create(bool bScrol,CTexture::Type type, CScene::OBJTYPE objtype)
{
	//�C���X�^���X����
	CBg *pBg = new CBg(objtype);

	if (pBg != NULL)
	{
		// ���̎擾
		pBg->m_Type = type;
		pBg->m_bCanScroll = bScrol;

		// ����������
		pBg->Init();
	}
	return pBg;
}

//---------------------------------------------------------------
// �w�i�ړ��̌��E�l
//---------------------------------------------------------------
void CBg::BgLimit(void)
{
	//--------------------------
	// �w�i�X�N���[���͈�
	//----------------------------
	if (m_pos.x >= m_SpreadRange_max.x)	// �ő�g��w
	{
		m_pos.x = m_SpreadRange_max.x;
	}
	if (m_pos.x <= m_SpreadRange_min.x)	// �ŏ��g��w
	{
		m_pos.x = m_SpreadRange_min.x;
	}
	if (m_pos.y >= m_SpreadRange_max.y)	// �ő�g��x
	{
		m_pos.y = m_SpreadRange_max.y;
	}
	if (m_pos.y <= m_SpreadRange_min.y)	// �ŏ��g��x
	{
		m_pos.y = m_SpreadRange_min.y;
	}
}

