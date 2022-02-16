//=============================================================================
//
// �e�N�X�`������ [texture.h]
// Author : 
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTexture
{
public:
	CTexture();			// �f�t�H���g�R���X�g���N�^
	~CTexture();		// �f�t�H���g�f�X�g���N�^

	typedef enum
	{
		None = -1,		// �e�N�X�`������
		Prov,			// ���e�N�X�`��
		Bg,				// �w�i
		Title,			// �^�C�g�����
		Result,			// ���U���g���
		Player,			// �v���C���[
		Enemy,			// �G
		Bullet,			// �e
		Number,			// ����
		Effect,			// �G�t�F�N�g
		Target,			// �^�[�Q�b�g
		Explosion,		// ����
		Gauge,			// �Q�[�W
		GaugeFrame,		// �Q�[�W�t���[��
		MapFrame,		// �~�j�}�b�v�̘g
		Rank1,			// 1�ʃe�N�X�`��
		Rank2,			// 2�ʃe�N�X�`��
		Rank3,			// 3�ʃe�N�X�`��
		Rank4,			// 4�ʃe�N�X�`��
		Rank5,			// 5�ʃe�N�X�`��
		GameBack,		// �Q�[���ɖ߂�
		Retry,			// ���g���C
		TitleBack,		// �^�C�g���ɖ߂�
		Cursol,			// �J�[�\��
		PressEnter,		// �v���X�G���^�[
		Tutorial01,		// �`���[�g���A��1
		Tutorial02,		// �`���[�g���A��2
		Max,			// �e�N�X�`���̍ő吔
	} Type;

	void Init(void);	// �e�N�X�`���̐���
	void Uninit(void);	// �I��
	LPDIRECT3DTEXTURE9 GetTexture(Type Type) { return m_pTexture[Type]; }	// �e�N�X�`���̊��蓖��(�e�N�X�`���̎��) { return �I�񂾃e�N�X�`����Ԃ� }

private:
	LPDIRECT3DTEXTURE9	m_pTexture[Max];	// �e�N�X�`��
};

#endif