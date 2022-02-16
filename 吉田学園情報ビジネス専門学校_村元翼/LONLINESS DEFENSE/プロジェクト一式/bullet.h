//=============================================================================
// �e����
// Author : ������
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_
#include "scene2D.h"

//=============================================================================
// �O���錾
//=============================================================================
class CTexture;
class CEffect;
class CMiniPolygon;

//=============================================================================
// �N���X�錾
//=============================================================================
class CBullet : public CScene2D
{
public:
	CBullet(OBJTYPE nPriority = OBJTYPE_BULLET);		// �R���X�g���N�^
	~CBullet();											// �f�X�g���N�^

	HRESULT Init(void);									// ������
	void Uninit(void);									// �I��
	void Update(void);									// �X�V
	void Draw(void);									// �`��
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,float angle, CTexture::Type texture = CTexture::Bullet);// ����

	// Getter
	D3DXVECTOR3 GetPos(void)	{ return m_pos; }
	D3DXVECTOR3 GetScale(void)	{ return m_scale; }
	bool		GetUse(void)	{ return m_bUse; }
	static int	GetAll(void)	{ return m_nAll; }

private:
	D3DXVECTOR3		m_pos;			// �ʒu
	D3DXVECTOR3		m_scale;		// �T�C�Y
	D3DXVECTOR3		m_move;			// �ړ���
	float			m_fAngle;		// �p�x
	float			m_fSpeed;		// ���x
	int				m_nLifeSpan;	// ����
	bool			m_bUse;			// �g�p��
	CTexture::Type	m_Tex;			// �e�N�X�`���^�C�v
	CEffect			*m_pEffect;		// �G�t�F�N�g�N���X
	CMiniPolygon	*m_pMiniBullet;	// �~�j�|���S���N���X
	static int		m_nAll;			// �e�̑���
};

#endif // _BULLET_H_
