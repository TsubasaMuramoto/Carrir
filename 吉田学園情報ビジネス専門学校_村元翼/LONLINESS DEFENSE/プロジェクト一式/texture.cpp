//=============================================================================
//
// �e�N�X�`������ [texture.cpp]
//
//=============================================================================
#include "texture.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
void CTexture::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;							// �f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();		// �f�o�C�X���擾����

	D3DXCreateTextureFromFile
	(
		pDevice,
		"",									// ����
		&m_pTexture[None]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Flag.png",			// ��
		&m_pTexture[Prov]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Player.png",			// �v���C���[
		&m_pTexture[Player]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Bullet.png",			// �e
		&m_pTexture[Bullet]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Enemy.png",			// �G
		&m_pTexture[Enemy]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Bg.jpg",				// �w�i
		&m_pTexture[Bg]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/title.png",			// �^�C�g�����
		&m_pTexture[Title]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Bg.jpg",				// ���U���g���
		&m_pTexture[Result]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/number000.png",		// �i���o�[
		&m_pTexture[Number]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Effect000.jpg",		// �G�t�F�N�g
		&m_pTexture[Effect]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Earth.png",			// �^�[�Q�b�g
		&m_pTexture[Target]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Explosion003.png",	// ����
		&m_pTexture[Explosion]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Gauge000.png",		// �Q�[�W
		&m_pTexture[Gauge]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/GaugeFrame000.png",	// �Q�[�W�t���[��
		&m_pTexture[GaugeFrame]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/MapFrame001.png",		// �}�b�v�t���[��
		&m_pTexture[MapFrame]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/1st.png",				// 1��
		&m_pTexture[Rank1]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/2nd.png",				// 2��
		&m_pTexture[Rank2]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/3rd.png",				// 3��
		&m_pTexture[Rank3]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/4th.png",				// 4��
		&m_pTexture[Rank4]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/5th.png",				// 5��
		&m_pTexture[Rank5]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/ReturnGame.png",		// �Q�[���ɖ߂�
		&m_pTexture[GameBack]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Retry.png",			// ���g���C
		&m_pTexture[Retry]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/ReturnTitle.png",		// �^�C�g���ɖ߂�
		&m_pTexture[TitleBack]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/right.png",			// �J�[�\��
		&m_pTexture[Cursol]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/press.png",			// �v���X�G���^�[
		&m_pTexture[PressEnter]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Tutorial001.png",		// �`���[�g���A��1
		&m_pTexture[Tutorial01]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Tutorial002.png",		// �`���[�g���A��2
		&m_pTexture[Tutorial02]
	);
}

//=============================================================================
// �I��
//=============================================================================
void CTexture::Uninit(void)
{
	for (int nCntTexture = 0; nCntTexture < Max; nCntTexture++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCntTexture] != nullptr)
		{
			m_pTexture[nCntTexture]->Release();
			m_pTexture[nCntTexture] = nullptr;
		}
	}
}