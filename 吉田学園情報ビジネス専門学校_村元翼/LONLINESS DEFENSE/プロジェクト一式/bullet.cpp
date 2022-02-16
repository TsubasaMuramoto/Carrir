//=============================================================================
//
// �e
// Author : ������
//
//=============================================================================
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "scene.h"
#include "keyboard.h"
#include "effect.h"
#include "collision.h"
#include "enemy.h"
#include "player.h"
#include "game.h"
#include "score.h"
#include "MiniPolygon.h"
#include "game.h"

//=============================================================================
// �ÓI�����o�ϐ��̏�����
//=============================================================================
int CBullet::m_nAll = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBullet::CBullet(OBJTYPE nPriority) : CScene2D(nPriority)
{
	// �����o�ϐ��̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLifeSpan = 0;
	m_fSpeed = 0;
	m_bUse = false;

	// �e���̃J�E���g
	m_nAll++;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{
	if (m_pEffect != nullptr)
	{
		m_pEffect->Uninit();
		delete m_pEffect;
		m_pEffect = nullptr;
	}

	if (m_pMiniBullet != nullptr)
	{
		m_pMiniBullet->Uninit();
		delete m_pMiniBullet;
		m_pMiniBullet = nullptr;
	}

	m_nAll--;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CBullet::Init(void)
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
void CBullet::Uninit(void)
{
	m_bUse = false;
	CScene2D::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CBullet::Update(void)
{
	if (m_bUse == true)
	{
		CScene2D::Update();							// 2D�|���S���X�V
		CScene2D::SetPos(m_pos, m_scale);			// �ʒu�̍X�V
		m_pos = CScene::GetPos();					// �ʒu�̎擾

		m_pMiniBullet->Move(-m_move);

		// ��ʊO�ɍs��
		if (m_pos.x <= (-CGame::GetScrollPos().x / 2) ||
			m_pos.x >= (SCREEN_WIDTH * 2) - (CGame::GetScrollPos().x / 2) ||
			m_pos.y <= (-CGame::GetScrollPos().y / 2) ||
			m_pos.y >= (SCREEN_HEIGHT * 2) - (CGame::GetScrollPos().y / 2))
		{
			Uninit();
		}

		// �e�̎�������
		if (m_nLifeSpan <= 0)
		{
			Uninit();
		}

		else
		{
			m_nLifeSpan--;												// �e�̎��������炷
			m_move = CScene2D::Move(&m_pos, m_fAngle, m_fSpeed);		// �e�̈ړ�
		}

		//----------------------------------------------------------------------
		// �G�Ƃ̓����蔻��
		//----------------------------------------------------------------------
		CCollision *pCollision = new CCollision;
		CScene *pScene = CScene::GetScene(CScene::OBJTYPE_ENEMY);

		while (pScene != nullptr)
		{
			CScene *pSceneNext = CScene::GetSceneNext(pScene);

			if (pScene != nullptr)
			{
				// �~�Ǝl�p�̓����蔻��
				if (pCollision->CircleCollision(this, pScene) == true)
				{
					CEffect::Create(
						m_pos,
						D3DXVECTOR3(m_fSpeed, m_fSpeed, 0.0f),
						D3DXVECTOR3(150.0f,150.0f,0.0f),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						0.0f, 0.0f, 0.0f,
						CEffect::EFFECT_EXPLOSION,
						CTexture::Explosion);		// �����G�t�F�N�g����

					CScore *pScore;
					pScore = CGame::GetScore();		// �X�R�A�擾
					pScore->AddScore(100);			// �X�R�A���Z
					Uninit();						// �e�̏���
					pScene->Uninit();				// �G�̏���
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
}

//=============================================================================
// �`��
//=============================================================================
void CBullet::Draw(void)
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
// �e�̐���
//=============================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,float angle, CTexture::Type texture)
{
	// �C���X�^���X����
	CBullet *pBullet = new CBullet(OBJTYPE_BULLET);

	// �v���C���[���̎擾
	pBullet->m_pos = pos;							// �ʒu
	pBullet->m_scale = scale;						// �傫��
	pBullet->m_fAngle = angle;						// �p�x
	pBullet->m_Tex = texture;						// �e�N�X�`��
	pBullet->m_nLifeSpan = 60;						// ���C�t
	pBullet->m_fSpeed = 15.0f;						// ���x
	pBullet->m_bUse = true;							// �e�̎g�p��

	if (pBullet != nullptr)
	{
		pBullet->Init();	// ����������

	// �G�t�F�N�g�̐���
		pBullet->m_pEffect = CEffect::Create
		(
			pBullet->m_pos,												// �ʒu
			D3DXVECTOR3(pBullet->m_fSpeed, pBullet->m_fSpeed, 0.0f),	// ���x
			D3DXVECTOR3(60.0f, 60.0f, 0.0f),							// �傫��
			D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f),							// �J���[
			0.1f,														// �k�����x
			0.01f,														// ���������x
			pBullet->m_fAngle,											// �p�x
			CEffect::EFFECT_BULLET,										// �G�t�F�N�g�^�C�v
			CTexture::Effect											// �e�N�X�`���^�C�v
		);

		// �~�j�}�b�v�̒e�̐���
		pBullet->m_pMiniBullet = CMiniPolygon::Create
		(
			D3DXVECTOR3							// �ʒu
			(
				pBullet->GetPos().x,
				pBullet->GetPos().y,
				0.0f
			),
			D3DXVECTOR3							// �T�C�Y
			(
				pBullet->GetScale().x,
				pBullet->GetScale().y,
				0.0f
			),
			CMiniPolygon::MINIPOLYGON_BULLET	// �~�j�}�b�v�̃|���S���̃^�C�v
		);
	}

	return pBullet;
}
