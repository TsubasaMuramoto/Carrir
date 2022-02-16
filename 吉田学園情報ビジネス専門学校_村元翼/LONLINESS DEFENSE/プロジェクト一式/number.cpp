//================================================
//�i���o�[����
//Author:��������
//================================================
#include "renderer.h"
#include "number.h"
#include "manager.h"
#include "scene.h"
#include "texture.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CNumber::CNumber()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CNumber::~CNumber()
{

}

//================================================
//����������
//================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//�ϐ�������
	m_pos = pos;
	m_size = size;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D_NUMBER) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D_NUMBER,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	VERTEX_2D_NUMBER *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2.0f, m_pos.y - m_size.y / 2.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2.0f, m_pos.y - m_size.y / 2.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2.0f, m_pos.y + m_size.y / 2.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2.0f, m_pos.y + m_size.y / 2.0f, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f / 10.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f / 10.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
//�I������
//================================================
void CNumber::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//================================================
//�X�V����
//================================================
void CNumber::Update(void)
{

}

//================================================
//�`�揈��
//================================================
void CNumber::Draw(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D_NUMBER));
	pDevice->SetFVF(FVF_VERTEX_2D_NUMBER);			// ���_�t�H�[�}�b�g�̐ݒ�

	pDevice->SetTexture(0, m_pTexture);				// �e�N�X�`���̐ݒ�

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
		0,											// �`����J�n���钸�_�̃C���f�b�N�X
		2);											// �`�悷��v���~�e�B�u��
}

//================================================
//��������
//================================================
CNumber* CNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X�̐���
	CNumber *pNumber = NULL;
	if (pNumber == NULL)
	{
		pNumber = new CNumber;
		if (pNumber != NULL)
		{
			m_pTexture = CManager::GetTexture()->GetTexture(CTexture::Number);
			pNumber->Init(pos, size);
		}
	}
	return pNumber;
}

//================================================
// �v�Z����(������)
//================================================

//================================================
//�e�N�X�`���ݒ菈��
//================================================
void CNumber::SetNumber(int nNumber)
{
	VERTEX_2D_NUMBER *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f + ((1.0f / 10.0f) * nNumber), 0.0f);
	pVtx[1].tex = D3DXVECTOR2((1.0f / 10.0f) + ((1.0f / 10.0f) * nNumber), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + ((1.0f / 10.0f) * nNumber), 1.0f);
	pVtx[3].tex = D3DXVECTOR2((1.0f / 10.0f) + ((1.0f / 10.0f) * nNumber), 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�J���[�ݒ菈��
//================================================
void CNumber::SetCol(D3DCOLORVALUE col)
{
	VERTEX_2D_NUMBER *pVtx;	// ���_���
							//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);
	pVtx[1].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);
	pVtx[2].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);
	pVtx[3].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�J���[�ݒ菈��
//================================================
void CNumber::SetCol(D3DXCOLOR col)
{
	VERTEX_2D_NUMBER *pVtx;	// ���_���
							//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�ʒu�ݒ菈��
//================================================
void CNumber::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	VERTEX_2D_NUMBER *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2.0f, m_pos.y - m_size.y / 2.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2.0f, m_pos.y - m_size.y / 2.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2.0f, m_pos.y + m_size.y / 2.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2.0f, m_pos.y + m_size.y / 2.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}