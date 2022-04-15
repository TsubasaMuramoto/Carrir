//=============================================================================
//
// MiniPolygon����
// Author : ������
//
//=============================================================================
#include "MiniPolygon.h"
#include "polygon.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "enemy.h"
#include "game.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMiniPolygon::CMiniPolygon(OBJTYPE nPriority) : CScene2D(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUse = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMiniPolygon::~CMiniPolygon()
{
}

//=============================================================================
// ������
//=============================================================================
HRESULT CMiniPolygon::Init(void)
{
	// CScene2D::BindTexture(m_Tex);
	CScene2D::Init();
	CScene2D::SetPos(m_pos, m_scale);
	CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CMiniPolygon::Uninit(void)
{
	m_bUse = false;
	CScene2D::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CMiniPolygon::Update(void)
{
	if (m_bUse)
	{
		CScene2D::Update();

		// �^�C�v�ʍX�V����
		switch (m_type)
		{
		case MINIPOLYGON_PLAYER:
			Move(CScene::GetScene(OBJTYPE_PLAYER)->GetMove());
			SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			break;

		case MINIPOLYGON_ENEMY:
			SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;

		case MINIPOLYGON_TARGET:
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void CMiniPolygon::Draw(void)
{
	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �A���t�@�u�����h
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);

	CScene2D::Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
}

//=============================================================================
// �~�j�|���S���̐���
//=============================================================================
CMiniPolygon *CMiniPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, MINIPOLYGON_TYPE type)
{
	//�C���X�^���X����
	CMiniPolygon *pMiniPolygon = new CMiniPolygon(OBJTYPE_POLYGON);

	if (pMiniPolygon != nullptr)
	{
		//						���~�j�}�b�v�̉E����n�_��		���X�N���[���������̈ʒu��2�Ŋ���pos�ɑ����A�ʒu���~�j�|���S���̑傫���Ŋ���
		pMiniPolygon->m_pos = CPolygon::GetVtx1() + ((pos +(CGame::GetScrollPos() / 2)) / DIVISION_SIZE);
		pMiniPolygon->m_scale = scale / DIVISION_SIZE;
		pMiniPolygon->m_type = type;
		pMiniPolygon->m_bUse = true;
		
		// �^�C�v�ʏ���������
		switch (pMiniPolygon->m_type)
		{
		case MINIPOLYGON_PLAYER:
			break;

		case MINIPOLYGON_ENEMY:
			
			break;

		case MINIPOLYGON_TARGET:
			pMiniPolygon->BindTexture(CTexture::Target);
			break;
		}

		// ����������
		pMiniPolygon->Init();
	}

	return pMiniPolygon;
}

//=============================================================================
// �ړ�
//=============================================================================
void CMiniPolygon::Move(D3DXVECTOR3 speed)
{
	// �ړ��ʂ�0�ȊO�̎�
	if (speed.x != 0.0f || speed.y != 0.0f)
	{
		// ���W�X�V
		if (speed.x != 0.0f)
		{
			m_pos.x += (speed.x / DIVISION_SIZE);
		}
		if (speed.y != 0.0f)
		{
			m_pos.y += (speed.y / DIVISION_SIZE);
		}

		CScene2D::SetPos(m_pos, m_scale, false);
	}
}