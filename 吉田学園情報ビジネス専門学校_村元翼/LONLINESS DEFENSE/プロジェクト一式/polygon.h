//=============================================================================
//
// Polygon����
// Author : ������
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_
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
class CPolygon : public CScene2D
{
public:

	CPolygon(OBJTYPE nPriority = OBJTYPE_POLYGON);		// �R���X�g���N�^
	~CPolygon();										// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, CTexture::Type texture = CTexture::Prov);

	//-------------------------
	// Getter & Setter
	//-------------------------
	void SetPos(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void)	{ return m_pos; }
	D3DXVECTOR3 GetScale(void)	{ return m_scale; }
	static D3DXVECTOR3 GetVtx1(void)	{ return m_Vtx1; }
	static D3DXVECTOR3 GetVtx2(void)	{ return m_Vtx2; }

private:
	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXVECTOR3 m_scale;		// �T�C�Y
	static D3DXVECTOR3 m_Vtx1;	// ���_(����)
	static D3DXVECTOR3 m_Vtx2;	// ���_(�E��)
	CTexture::Type m_Tex;		// �e�N�X�`���^�C�v
};

#endif // _POLYGON_H_
