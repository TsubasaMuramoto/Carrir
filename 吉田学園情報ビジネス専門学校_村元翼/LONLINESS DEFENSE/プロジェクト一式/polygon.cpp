//=============================================================================
//
// Polygon����
// Author : ������
//
//=============================================================================
#include "polygon.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"

//=============================================================================
// �ÓI�����o�ϐ��̏�����
//=============================================================================
D3DXVECTOR3 CPolygon::m_Vtx1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CPolygon::m_Vtx2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPolygon::CPolygon(OBJTYPE nPriority) : CScene2D(nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPolygon::~CPolygon()
{

}

//------------------------------------------------------------
// ���_���W�̐ݒ�
//------------------------------------------------------------
void CPolygon::SetPos(D3DXVECTOR3 pos)
{
	CScene::SetPos(pos);

	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�o�b�t�@�̐���
	pVtx[0].pos = D3DXVECTOR3(pos.x - (m_scale.x / 2), pos.y - (m_scale.y / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + (m_scale.x / 2), pos.y - (m_scale.y / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - (m_scale.x / 2), pos.y + (m_scale.y / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + (m_scale.x / 2), pos.y + (m_scale.y / 2), 0.0f);

	// ���_�擾
	m_Vtx1 = pVtx[0].pos;
	m_Vtx2 = pVtx[3].pos;

	m_pVtxBuff->Unlock();
}

//=============================================================================
// ������
//=============================================================================
HRESULT CPolygon::Init(void)
{
	CScene2D::BindTexture(m_Tex);
	CScene2D::Init();
	CPolygon::SetPos(m_pos);
	CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CPolygon::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CPolygon::Update(void)
{
	CScene2D::Update();
}

//=============================================================================
// �`��
//=============================================================================
void CPolygon::Draw(void)
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
// �|���S���̐���
//=============================================================================
CPolygon *CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, CTexture::Type texture)
{
	//�C���X�^���X����
	CPolygon *pPolygon = new CPolygon(OBJTYPE_POLYGON);

	pPolygon->m_pos = pos;
	pPolygon->m_scale = scale;
	pPolygon->m_Tex = texture;

	if (pPolygon != NULL)
	{
		pPolygon->Init();
	}

	return pPolygon;
}