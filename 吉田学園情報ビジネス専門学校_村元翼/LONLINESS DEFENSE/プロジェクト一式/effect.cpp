//--------------------------------------------------
// �G�t�F�N�g�̍쐬
// Author : ������
//--------------------------------------------------
#include "main.h"
#include "effect.h"
#include "manager.h"
#include "renderer.h"
#include "bullet.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CEffect::CEffect(OBJTYPE nPriority) : CScene2D(nPriority)
{
	m_fAngle = 0.0f;
	m_fScaleSpeed = 0.0f;
	m_nAnimCounter = 0;
	m_Pattern = D3DXVECTOR2(0.0f, 0.0f);
	m_bDoOnce = false;
	m_bUse = false;
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CEffect::~CEffect()
{

}

//---------------------------------------------------
// �G�t�F�N�g����
//---------------------------------------------------
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col,float ScaleSpeed, float TransparentSpeed, float angle, EFFECT_TYPE effectType,CTexture::Type type)
{//	�ʒu, �ړ���, �T�C�Y,�F, �������Ȃ�X�s�[�h

	// �C���X�^���X����
	CEffect *pEffect = nullptr;
	if (pEffect == nullptr)
	{
		pEffect = new CEffect(OBJTYPE_EFFECT);

		if (pEffect != nullptr)
		{
			// �������
			pEffect->m_pos = pos;
			pEffect->m_move = move;
			pEffect->m_size = size;
			pEffect->m_col = col;
			pEffect->m_fScaleSpeed = ScaleSpeed;
			pEffect->m_fTransparentSpeed = TransparentSpeed;
			pEffect->m_fAngle = angle;
			pEffect->m_EffectType = effectType;
			pEffect->m_bUse = true;
			pEffect->Init(type);								// �摜�ǂݍ���
		}
	}

	return pEffect;
}

//----------------------------------------------------
// ����������
//-----------------------------------------------------
HRESULT CEffect::Init(CTexture::Type type)
{
	CScene2D::BindTexture(type);
	CScene2D::Init();
	CScene2D::SetPos(m_pos, m_size);
	CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

HRESULT CEffect::Init()
{
	return S_OK;
}

//---------------------------------------------------------
// �I������
//---------------------------------------------------------
void CEffect::Uninit()
{
	m_bUse = false;
	CScene2D::Uninit();
}

//----------------------------------------------------
// �X�V
//-----------------------------------------------------
void CEffect::Update()
{
	if (m_bUse == true)
	{
		CScene2D::SetPos(m_pos, m_size);	// ���_���̐ݒ�(�X�V)
		CScene2D::SetCol(m_col);			// �J���[�̐ݒ�(�X�V)
		m_pos = CScene::GetPos();			// �ʒu�̎擾

		ProcessByType(m_EffectType);		// �^�C�v�ʃG�t�F�N�g����

		// X��Y�̃T�C�Y��0�ɂȂ��������
		if (m_size.x <= 0 && m_size.y <= 0)
		{
			Uninit();
		}

		//���l��0�ȉ��ɂȂ����������
		if (m_col.a <= 0.0)
		{
			Uninit();
		}
	}
}

//----------------------------------------------------
// �`��
//-----------------------------------------------------
void CEffect::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̃|�C���^

	// ���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	// ���̐ݒ�ɖ߂�
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//----------------------------------------------------
// �G�t�F�N�g�^�C�v�ʏ���
//-----------------------------------------------------
void CEffect::ProcessByType(EFFECT_TYPE type)
{
	//---------------------------------------------------
	// ��x�����s������
	//---------------------------------------------------
	if (m_bDoOnce == false)
	{
		switch (type)
		{
		case EFFECT_BULLET:
			break;

		case EFFECT_PLAYER:
			RandomInjection();
			break;

		case EFFECT_EXPLOSION:
			break;
		}
		m_bDoOnce = true;
	}

	//---------------------------------------------------
	// �J��Ԃ�����
	//---------------------------------------------------
	switch (type)
	{
	case EFFECT_BULLET:
		CScene2D::Move(&m_pos, m_fAngle, m_move.x);	
		//m_col.a -= m_fTransparentSpeed;	// ���邳��������
		break;

	case EFFECT_PLAYER:
		CScene2D::Move(&m_pos, m_fAngle, 2.0f);
		break;

	case EFFECT_EXPLOSION:
		CScene2D::SetTex(m_Pattern.x, m_Pattern.y, 0.2f, 0.5f);
		EffectAnim(m_nAnimCounter, 3, m_Pattern, D3DXVECTOR2(5.0f,2.0f));
		break;
	}

	// �G�t�F�N�g���������Ȃ��Ă�������
	m_size.x -= m_fScaleSpeed;
	m_size.y -= m_fScaleSpeed;
}

//----------------------------------------------------
// ������Ƀ����_���ɕ��˂���G�t�F�N�g�̏���
//-----------------------------------------------------
void CEffect::RandomInjection(void)
{
	// ���˃G�t�F�N�g�̊p�x���̍ŏ��l�Ǝ���l
	float minRange = D3DXToRadian(-90.0f);
	float maxRange = D3DXToRadian(90.0f);

	std::random_device Randseed;												// ����������ŃV�[�h�l�����S�����_���ɏ���������
	std::mt19937_64 mt(Randseed());												// �^�����������o��
	std::uniform_real_distribution<float> Dist(minRange, maxRange);				// �w�肵���͈͓��̐��l�𓙊m���ŕԂ�(�ŏ��l�ȏ�A�ő�l"����")

	m_fAngle = Dist(mt);

#if _DEBUG_
	float fDegree = D3DXToDegree(m_fAngle);										// �f�o�b�O���Ɋp�x���m�F���邽�߂̏���
#endif

	if (m_move.x != 0.0f)		// ���E
	{
		m_fAngle += D3DXToRadian(-90.0f);
	}
}

//----------------------------------------------------
// �G�t�F�N�g�̃A�j���[�V����
//-----------------------------------------------------
void CEffect::EffectAnim(int &nAnimCounter, int nSpan, D3DXVECTOR2 &Pattern, D3DXVECTOR2 MaxPattern)
{
	nAnimCounter++;						// �J�E���^�[��i�߂�

	if (nAnimCounter >= nSpan)			// �J�E���^�[������
	{
		nAnimCounter = 0;
		Pattern.x++;
	}

	if (Pattern.x >= MaxPattern.x)		// �A�j���[�V�����p�^�[��X���ő�
	{
		Pattern.x = 0;
		Pattern.y++;
	}

	if (Pattern.y >= MaxPattern.y)		// �A�j���[�V�����p�^�[��Y���ő�
	{
		Pattern.y = 0;
		Uninit();
	}
}
