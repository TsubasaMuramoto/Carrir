//=============================================================================
//
// MiniPolygon処理
// Author : 村元翼
//
//=============================================================================
#ifndef _MINIPOLYGON_H_
#define _MINIPOLYGON_H_
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
class CMiniPolygon : public CScene2D
{
public:
	//==========================================================
	// ミニポリゴンタイプの構造体
	//==========================================================
	typedef enum
	{
		MINIPOLYGON_PLAYER = 0,
		MINIPOLYGON_ENEMY,
		MINIPOLYGON_TARGET,
		MINIPOLYGON_BULLET,
		MINIPOLYGON_MAX
	}MINIPOLYGON_TYPE;

	CMiniPolygon(OBJTYPE nPriority = OBJTYPE_POLYGON);		// コンストラクタ
	~CMiniPolygon();										// デストラクタ

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
	D3DXVECTOR3			m_pos;		// 位置
	D3DXVECTOR3			m_scale;	// サイズ
	MINIPOLYGON_TYPE	m_type;		// ミニポリゴンタイプ
	CTexture::Type		m_Tex;		// テクスチャタイプ
	bool				m_bUse;		// 使用状況
};

#endif // _MINIPOLYGON_H_
