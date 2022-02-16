//=============================================================================
//
// �G����
// Author : ������
//
//=============================================================================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "keyboard.h"
#include "score.h"
#include "game.h"
#include "polygon.h"
#include "MiniPolygon.h"
#include "collision.h"
#include "effect.h"

//=============================================================================
// �ÓI�����o�ϐ��̏�����
//=============================================================================
int CEnemy::m_nAll = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy(OBJTYPE nPriority) : CScene2D(nPriority)
{
	// �����o�ϐ��̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_nFrame = 0;
	m_nPattern = 0;
	m_bUse = false;

	// �G�̐��J�E���g
	m_nAll++;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{
	m_nAll--;
}

//------------------------------------------------------------
// ���_���W�̐ݒ�
//------------------------------------------------------------
void CEnemy::SetPos(D3DXVECTOR3 pos)
{
	CScene::SetPos(pos);

	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�o�b�t�@�̐���
	pVtx[0].pos = D3DXVECTOR3(pos.x - m_scale.x, pos.y - m_scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + m_scale.x, pos.y - m_scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - m_scale.x, pos.y + m_scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + m_scale.x, pos.y + m_scale.y, 0.0f);

	m_pVtxBuff->Unlock();

}
//=============================================================================
// ������
//=============================================================================
HRESULT CEnemy::Init(void)
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
void CEnemy::Uninit(void)
{
	if (m_pMiniEnemy != nullptr)
	{
		m_pMiniEnemy->Uninit();
		delete m_pMiniEnemy;
		m_pMiniEnemy = nullptr;
	}

	m_bUse = false;
	CScene2D::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CEnemy::Update(void)
{
	if (m_bUse == true)
	{
		// �~�j�}�b�v�̓G�̈ړ�
		m_pMiniEnemy->Move(m_move);

		CScene2D::Update();
		CScene2D::SetPos(m_pos, m_scale);
		CScene2D::SetTex((float)m_nPattern, 0.0f, 0.5f, 1.0f);
		m_pos = CScene::GetPos();

		//----------------------------------------------------------------------
		// �^�[�Q�b�g�Ƃ̓����蔻��
		//----------------------------------------------------------------------
		CScene *pScene = CScene::GetScene(CScene::OBJTYPE_TARGET);
		while (pScene != NULL)
		{
			// ���̃V�[�����擾
			CScene *pSceneNext = CScene::GetSceneNext(pScene);

			// �^�[�Q�b�g�ɒǏ]���鏈��
			FeaturedTarget(&pScene->GetPos(), &m_pos);

			// ���̃V�[�������݂̃V�[���ɂ���
			pScene = pSceneNext;	
		}

		//----------------------------------------------------------------------
		// �v���C���[�Ƃ̓����蔻��
		//----------------------------------------------------------------------
		CCollision *pCollision = new CCollision;
		CScene *pScene2 = CScene::GetScene(CScene::OBJTYPE_PLAYER);
		while (pScene2 != NULL)
		{
			// ���̃V�[�����擾
			CScene *pSceneNext2 = CScene::GetSceneNext(pScene2);

			if (pScene2 != NULL)
			{
				// �l�p�Ǝl�p�̓����蔻��
				if (pCollision->SetCollision(this, pScene2) == true)
				{
					CEffect::Create(
						m_pos,
						m_Speed,
						D3DXVECTOR3(150.0f, 150.0f, 0.0f),
						D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
						0.0f, 0.0f, 0.0f,
						CEffect::EFFECT_EXPLOSION,
						CTexture::Explosion);			// �����̃G�t�F�N�g����

					CScore *pScore = CGame::GetScore();	// �X�R�A�擾
					pScore->AddScore(100);				// �X�R�A���Z
					Uninit();							// �G�̏���
				}
			}

			// ���̃I�u�W�F�N�g������
			pScene2 = pSceneNext2;
		}

		if (pCollision != nullptr)
		{
			delete pCollision;
			pCollision = nullptr;
		}


	}

	// �t���[���J�E���g
	m_nFrame++;

	// �G�A�j���[�V������i�߂�
	if (m_nFrame >= 30)
	{
		m_nFrame = 0;
		m_nPattern++;
	}

	// �A�j���[�V������0�ɖ߂�
	if (m_nPattern >= 2)
	{
		m_nPattern = 0;
	}
}

//=============================================================================
// �`��
//=============================================================================
void CEnemy::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̃|�C���^

	// �A���t�@�u�����h
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);

	CScene2D::Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
}

//=============================================================================
// �G�̐���
//=============================================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, CTexture::Type texture)
{
	// �C���X�^���X����
	CEnemy *pEnemy = new CEnemy(OBJTYPE_ENEMY);

	if (pEnemy != nullptr)
	{
		// �v���C���[���̎擾
		pEnemy->m_pos = pos;
		pEnemy->m_scale = scale;
		pEnemy->m_Tex = texture;
		pEnemy->m_nLife = 240;
		pEnemy->m_Speed = ENEMY_SPEED;
		pEnemy->m_bUse = true;

		// ����������
		pEnemy->Init();

		// �~�j�}�b�v�̓G�̐���
		pEnemy->m_pMiniEnemy = CMiniPolygon::Create
		(
			D3DXVECTOR3						// �ʒu
			(
				pEnemy->GetPos().x,
				pEnemy->GetPos().y,
				0.0f
			),
			D3DXVECTOR3						// �T�C�Y
			(
				pEnemy->GetScale().x,
				pEnemy->GetScale().y,
				0.0f
			),
			CMiniPolygon::MINIPOLYGON_ENEMY	// �~�j�}�b�v�̃|���S���^�C�v
		);
	}

	return pEnemy;
}

//=============================================================================
// �G�̈ړ�
//=============================================================================
void CEnemy::Move(void)
{
	// m_pos.x += m_nSpeed;
	// m_pos.y += m_nSpeed;
}

//=============================================================================
// �^�[�Q�b�g�ɑΏۂ����Ă�������
//=============================================================================
void CEnemy::FeaturedTarget(D3DXVECTOR3 *targetPos, D3DXVECTOR3 *featuredPos)
{
	// �^�[�Q�b�g�̈ʒu�ƒǏ]����I�u�W�F�N�g�̈ʒu�̍��������߂�
	float fLengthX = (targetPos->x - featuredPos->x);
	float fLengthY = (targetPos->y - featuredPos->y);

	// �΂߂̋��������߂�
	float fLengthTrue = sqrtf(fLengthX * fLengthX + fLengthY * fLengthY);

	// ���K��
	m_move.x = fLengthX / fLengthTrue;
	m_move.y = fLengthY / fLengthTrue;

	// ���x���|����
	m_move.x *= m_Speed.x;
	m_move.y *= m_Speed.y;

	// ���W�X�V
	featuredPos->x += m_move.x;
	featuredPos->y += m_move.y;

	CScene::SetMove(m_move);
}