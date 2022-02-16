//=============================================================================
// 弾処理
// Author : 村元翼
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_
#include "scene2D.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CTexture;
class CEffect;
class CMiniPolygon;

//=============================================================================
// クラス宣言
//=============================================================================
class CBullet : public CScene2D
{
public:
	CBullet(OBJTYPE nPriority = OBJTYPE_BULLET);		// コンストラクタ
	~CBullet();											// デストラクタ

	HRESULT Init(void);									// 初期化
	void Uninit(void);									// 終了
	void Update(void);									// 更新
	void Draw(void);									// 描画
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,float angle, CTexture::Type texture = CTexture::Bullet);// 生成

	// Getter
	D3DXVECTOR3 GetPos(void)	{ return m_pos; }
	D3DXVECTOR3 GetScale(void)	{ return m_scale; }
	bool		GetUse(void)	{ return m_bUse; }
	static int	GetAll(void)	{ return m_nAll; }

private:
	D3DXVECTOR3		m_pos;			// 位置
	D3DXVECTOR3		m_scale;		// サイズ
	D3DXVECTOR3		m_move;			// 移動量
	float			m_fAngle;		// 角度
	float			m_fSpeed;		// 速度
	int				m_nLifeSpan;	// 寿命
	bool			m_bUse;			// 使用状況
	CTexture::Type	m_Tex;			// テクスチャタイプ
	CEffect			*m_pEffect;		// エフェクトクラス
	CMiniPolygon	*m_pMiniBullet;	// ミニポリゴンクラス
	static int		m_nAll;			// 弾の総数
};

#endif // _BULLET_H_
