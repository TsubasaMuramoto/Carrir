//=============================================================================
//
// 弾処理
// Author : 村元翼
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_
#include "scene2D.h"

// 前方宣言
class CTexture;
class CEffect;
class CMiniPolygon;
class CBullet : public CScene2D
{
public:
	CBullet(OBJTYPE nPriority = OBJTYPE_BULLET);		// コンストラクタ
	~CBullet();											// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,float angle, CTexture::Type texture = CTexture::Bullet);

	D3DXVECTOR3 GetPos(void)	{ return m_pos; }
	D3DXVECTOR3 GetScale(void)	{ return m_scale; }
	bool		GetUse(void)	{ return m_bUse; }
	static int	GetAll(void)	{ return m_nAll; }

private:

	D3DXVECTOR3		m_pos;
	D3DXVECTOR3		m_scale;
	D3DXVECTOR3		m_move;
	float			m_fAngle;
	float			m_fSpeed;
	int				m_nLifeSpan;
	bool			m_bUse = false;
	CTexture::Type	m_Tex;
	CEffect			*m_pEffect;
	CMiniPolygon	*m_pMiniBullet;
	static int		m_nAll;
};

#endif // _BULLET_H_
