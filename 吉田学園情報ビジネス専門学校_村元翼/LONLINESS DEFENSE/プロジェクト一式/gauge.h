//-----------------------------------------------------
//ゲージ処理
//-----------------------------------------------------
#ifndef _GAUGE_H_
#define _GAUGE_H_
#include "scene.h"
#include "scene2D.h"
#include "texture.h"

//-----------------------------------------------------
// マクロ定義
//-----------------------------------------------------
#define MAX_GAUGE_WIDTH (400.0f)					// ゲージ幅
#define DECREASE_GAUGE (-30.0f)						// ゲージの減る量
#define GAUGE_POS (D3DXVECTOR3(50.0f,50.0f,0.0f))	// ゲージ位置

//-----------------------------------------------------
// クラスの生成
//-----------------------------------------------------
class CGauge : public CScene2D
{
public:
	CGauge(OBJTYPE nPriority = OBJTYPE_POLYGON);
	~CGauge();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGauge *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);	// 生成
	static void SetGauge(float Set);							// ゲージの増減

private:
	D3DXVECTOR3			m_pos;									// 位置
	static D3DXVECTOR3	m_Scale;								// ゲージの大きさ
	bool				m_bNextMode;							// 二重押し防止変数

};

#endif // !_TIME_H_
