//=============================================================================
//
// �^�[�Q�b�g����
// Author : ������
//
//=============================================================================
#ifndef _TARGET_H_
#define _TARGET_H_
#include "scene2D.h"

// �O���錾
class CTexture;
class CMiniPolygon;
class CTarget : public CScene2D
{
public:
	CTarget(OBJTYPE nPriority = OBJTYPE_TARGET);		// �R���X�g���N�^
	~CTarget();											// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CTarget *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, CTexture::Type texture = CTexture::Target);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetScale(void) { return m_scale; }

private:
	D3DXVECTOR3		m_pos;				// �ʒu
	D3DXVECTOR3		m_scale;			// �傫��
	int				m_nLife;			// �̗�
	int				m_nInvincibleTime;	// ���G����
	bool			m_bUse = false;		// �g�p����
	CTexture::Type	m_Tex;				// �e�N�X�`��
	CMiniPolygon	*m_pMiniTarget;		// �~�j�^�[�Q�b�g
};

#endif // _TARGET_H_
