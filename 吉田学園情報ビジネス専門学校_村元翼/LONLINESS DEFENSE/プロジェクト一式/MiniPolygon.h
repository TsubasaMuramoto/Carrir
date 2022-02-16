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
#define DIVISION_SIZE (8)

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
	// �񋓌^
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
	D3DXVECTOR3			m_pos;
	D3DXVECTOR3			m_scale;
	MINIPOLYGON_TYPE	m_type;
	CTexture::Type		m_Tex;
	bool				m_bUse;
};

#endif // _MINIPOLYGON_H_
