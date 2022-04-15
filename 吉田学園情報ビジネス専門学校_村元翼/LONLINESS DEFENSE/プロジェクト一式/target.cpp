//=============================================================================
// �e
// Author : ������
//=============================================================================
#include "target.h"
#include "collision.h"
#include "manager.h"
#include "renderer.h"
#include "effect.h"
#include "gauge.h"
#include "MiniPolygon.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTarget::CTarget(OBJTYPE nPriority) : CScene2D(nPriority)
{
	// �����o�ϐ��̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_nInvincibleTime = 0;
	m_bUse = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTarget::~CTarget()
{
	// �I�u�W�F�N�g�I��
	if (m_pMiniTarget != nullptr)
	{
		m_pMiniTarget->Uninit();
		m_pMiniTarget = nullptr;
	}
}

//=============================================================================
// ������
//=============================================================================
HRESULT CTarget::Init(void)
{
	CScene2D::BindTexture(m_Tex);
	CScene2D::Init();
	CScene2D::SetPos(m_pos, m_scale);
	CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CTarget::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CTarget::Update(void)
{
	CScene2D::Update();							// 2D�|���S���X�V
	CScene2D::SetPos(m_pos, m_scale);			// �ʒu�̍X�V
	m_pos = CScene::GetPos();					// �ʒu�̎擾

	//=============================================================
	// �G�Ƃ̓����蔻��
	//=============================================================
	CCollision *pCollision = new CCollision;
	CScene *pScene = CScene::GetScene(CScene::OBJTYPE_ENEMY);

	while (pScene != nullptr)
	{
		// ���݂̎��̃V�[��
		CScene *pSceneNext = CScene::GetSceneNext(pScene);

		// �����蔻��
		if (pScene != nullptr)
		{
			if (m_nInvincibleTime <= 0)
			{
				m_nInvincibleTime = 0;
				CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// �J���[��ʏ�ɖ߂�

				// �~�̓����蔻��
				if (pCollision->CircleCollision(this, pScene) == true)
				{
					if (m_nLife <= 0)	// �̗͂�0�ɂȂ�����
					{
						Uninit();
					}
					else				// �����łȂ���	
					{
						CEffect::Create(
							pScene->GetPos(),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							D3DXVECTOR3(150.0f, 150.0f, 0.0f),
							D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
							0.0f, 0.0f, 0.0f,
							CEffect::EFFECT_EXPLOSION,
							CTexture::Explosion);								// �����̃G�t�F�N�g����

						CGauge::SetGauge(DECREASE_GAUGE);						// �̗̓Q�[�W�����炷
						CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// �����ɂ���
						m_nLife--;												// �̗͂����炷
					}

					pScene->Uninit();											// �G�̏���
					m_nInvincibleTime = INVINCIBLE_TIME;						// �������^�C���̏�����
				}
			}

			else
			{
				m_nInvincibleTime--;
			}
		}

		// ���̃I�u�W�F�N�g������
		pScene = pSceneNext;
	}

	if (pCollision != nullptr)
	{
		delete pCollision;
		pCollision = nullptr;
	}

}

//=============================================================================
// �`��
//=============================================================================
void CTarget::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^

	// �A���t�@�u�����h
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);

	CScene2D::Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
}

//=============================================================================
// �^�[�Q�b�g�̐���
//=============================================================================
CTarget *CTarget::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, CTexture::Type texture)
{
	// �C���X�^���X����
	CTarget *pTarget = new CTarget(OBJTYPE_TARGET);

	// �v���C���[���̎擾
	if (pTarget != NULL)
	{
		pTarget->m_pos = pos;							// �ʒu
		pTarget->m_scale = scale;						// �傫��
		pTarget->m_Tex = texture;						// �e�N�X�`��
		pTarget->m_nLife = 100;							// �̗�
		pTarget->m_nInvincibleTime = 0;					// ���G����
		pTarget->m_bUse = true;							// �e�̎g�p��
		pTarget->Init();								// ����������

		pTarget->m_pMiniTarget = CMiniPolygon::Create	// �~�j�}�b�v�̃^�[�Q�b�g�̐���
		(
			D3DXVECTOR3							// �ʒu
			(
				pTarget->GetPos().x,
				pTarget->GetPos().y,
				0.0f
			),
			D3DXVECTOR3							// �T�C�Y
			(
				pTarget->GetScale().x,
				pTarget->GetScale().y,
				0.0f
			),
			CMiniPolygon::MINIPOLYGON_TARGET	// �^�C�v
		);
	}

	return pTarget;
}


