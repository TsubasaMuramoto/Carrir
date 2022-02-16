//=============================================================================
//
// ターゲット処理
// Author : 村元翼
//
//=============================================================================
#ifndef _TARGET_H_
#define _TARGET_H_
#include "scene2D.h"

// 前方宣言
class CTexture;
class CMiniPolygon;
class CTarget : public CScene2D
{
public:
	CTarget(OBJTYPE nPriority = OBJTYPE_TARGET);		// コンストラクタ
	~CTarget();											// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CTarget *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, CTexture::Type texture = CTexture::Target);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetScale(void) { return m_scale; }

private:
	D3DXVECTOR3		m_pos;				// 位置
	D3DXVECTOR3		m_scale;			// 大きさ
	int				m_nLife;			// 体力
	int				m_nInvincibleTime;	// 無敵時間
	bool			m_bUse = false;		// 使用判定
	CTexture::Type	m_Tex;				// テクスチャ
	CMiniPolygon	*m_pMiniTarget;		// ミニターゲット
};

#endif // _TARGET_H_
