//=============================================================================
//
// Polygon処理
// Author : 村元翼
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_
#include "scene2D.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 前方宣言
//=============================================================================
class CTexture;

//=============================================================================
// クラス定義
//=============================================================================
class CPolygon : public CScene2D
{
public:

	CPolygon(OBJTYPE nPriority = OBJTYPE_POLYGON);		// コンストラクタ
	~CPolygon();										// デストラクタ

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
	D3DXVECTOR3 m_pos;			// 位置
	D3DXVECTOR3 m_scale;		// サイズ
	static D3DXVECTOR3 m_Vtx1;	// 頂点(左上)
	static D3DXVECTOR3 m_Vtx2;	// 頂点(右下)
	CTexture::Type m_Tex;		// テクスチャタイプ
};

#endif // _POLYGON_H_
