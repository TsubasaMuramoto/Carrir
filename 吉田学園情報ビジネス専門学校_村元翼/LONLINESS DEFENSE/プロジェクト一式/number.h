//===========================================
//�i���o�[����
//Author:��������
//===========================================
#ifndef _NUMBER_H_
#define _NUMBER_H_
#include "main.h"

//================================================
//�}�N����`
//================================================
#define FVF_VERTEX_2D_NUMBER (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//���_�t�H�[�}�b�g
#define VERTEX_NUM_NUMBER (4)											//���_��

//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//���_���W
	float rhw;				//1.0f�ŌŒ�
	D3DCOLOR col;			//���_�J���[
	D3DXVECTOR2 tex;		//�e�N�X�`�����W
} VERTEX_2D_NUMBER;

//================================================
//�N���X�̒�`
//================================================
class CNumber
{
public:
	CNumber();			//�R���X�g���N�^
	~CNumber();			//�f�X�g���N�^

						//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);		//�i���o�[�ݒ菈��
	void SetCol(D3DCOLORVALUE col);		//�J���[�ݒ菈��
	void SetCol(D3DXCOLOR col);			//�J���[�ݒ菈��
	void SetPos(D3DXVECTOR3 pos);		//�ʒu�ݒ菈��

	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						//�|���S���̈ʒu
	D3DXVECTOR3	m_size;						// �T�C�Y
};

#endif // !_NUMBER_H_