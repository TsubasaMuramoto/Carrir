//=============================================================================
//
// MiniPolygon����
// Author : ������
//
//=============================================================================
#ifndef _MINIPOLYGON_H_
#define _MINIPOLYGON_H_
#include "scene2D.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �O���錾
//=============================================================================
class CTexture;

//=============================================================================
// �N���X��`
//=============================================================================
class CMiniPolygon : public CScene2D
{
public:
	//==========================================================
	// �~�j�|���S���^�C�v�̍\����
	//==========================================================
	typedef enum
	{
		MINIPOLYGON_PLAYER = 0,
		MINIPOLYGON_ENEMY,
		MINIPOLYGON_TARGET,
		MINIPOLYGON_BULLET,
		MINIPOLYGON_MAX
	}MINIPOLYGON_TYPE;

	CMiniPolygon(OBJTYPE nPriority = OBJTYPE_POLYGON);		// �R���X�g���N�^
	~CMiniPolygon();										// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMiniPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,MINIPOLYGON_TYPE type);
	void Move(D3DXVECTOR3 speed);

	//----------------------------------------------------------
	// Getter
	//----------------------------------------------------------
	D3DXVECTOR3 GetPos(void)	{ return m_pos; }
	D3DXVECTOR3 GetScale(void)  { return m_scale; }

private:
	D3DXVECTOR3			m_pos;		// �ʒu
	D3DXVECTOR3			m_scale;	// �T�C�Y
	MINIPOLYGON_TYPE	m_type;		// �~�j�|���S���^�C�v
	CTexture::Type		m_Tex;		// �e�N�X�`���^�C�v
	bool				m_bUse;		// �g�p��
};

#endif // _MINIPOLYGON_H_
