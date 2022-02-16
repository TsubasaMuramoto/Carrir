//=============================================================================
//
// 敵処理
// Author : 村元翼
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "scene2D.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ENEMY_SIZE (D3DXVECTOR3(50.0f,50.0f,0.0f))		// 敵サイズ
#define ENEMY_SPEED (D3DXVECTOR3(2.0f,2.0f,0.0f))		// 敵速度

//=============================================================================
// 前方宣言
//=============================================================================
class CTexture;
class CMiniPolygon;

//=============================================================================
// クラス
//=============================================================================
class CEnemy : public CScene2D
{
public:
	CEnemy(OBJTYPE nPriority = OBJTYPE_ENEMY);		// コンストラクタ
	~CEnemy();										// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, CTexture::Type texture = CTexture::Enemy);
	void Move(void);
	void FeaturedTarget(D3DXVECTOR3 *targetPos, D3DXVECTOR3 *featuredPos);				// ターゲットに向く処理

	//-------------------------------------------------
	// Getter & Setter
	//-------------------------------------------------
	void SetPos(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void)		{ return m_pos; }
	D3DXVECTOR3 GetScale(void)		{ return m_scale; }
	D3DXVECTOR3 GetMove(void)		{ return m_move; }
	static int	GetAll(void)		{ return m_nAll; }

private:
	int				m_nFrame ;		// フレーム数
	int				m_nPattern ;	// アニメーションパターン
	int				m_nLife;		// ライフ
	bool			m_bUse;			// 使用状況
	D3DXVECTOR3		m_pos;			// 位置
	D3DXVECTOR3		m_scale;		// サイズ
	D3DXVECTOR3		m_move;			// 移動量
	D3DXVECTOR3		m_Speed;		// 速度
	CTexture::Type	m_Tex;			// テクスチャタイプ
	CMiniPolygon	*m_pMiniEnemy;	// ミニポリゴンクラス
	static int		m_nAll;			// 敵の総数
};
#endif // _ENEMY_H_
