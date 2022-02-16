//--------------------------------------
// 背景
//--------------------------------------
#ifndef _BG_H
#define _BG_H
#include "scene2D.h"
#include "texture.h"

//-------------------------------------
// 前方宣言
//-------------------------------------
class CScene;

//-------------------------------------
// クラス生成
//-------------------------------------
class CBg : public CScene2D
{
public:
	CBg(OBJTYPE nPriority = OBJTYPE_BG);
	~CBg();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBg *Create(bool bScrol = true,CTexture::Type type = CTexture::Bg, CScene::OBJTYPE objtype = CScene::OBJTYPE_BG); // インスタンス生成処理
	void BgLimit(void);

	//-------------------------------------
	// Getter & Setter
	//-------------------------------------
	D3DXVECTOR3 GetTex(void)					{ return m_Tex; }
	D3DXVECTOR3 GetPos(void)					{ return m_pos; }
	static D3DXVECTOR2 GetRangeMin(void)		{ return m_SpreadRange_min; }
	static D3DXVECTOR2 GetRangeMax(void)		{ return m_SpreadRange_max; }

private:
	CTexture::Type				m_Type;			// テクスチャタイプ
	D3DXVECTOR3					m_Tex;			// テクスチャをスクロールする変数
	D3DXVECTOR3					m_pos;			// 位置
	bool						m_bScroll;		// スクロール切り替え
	bool						m_bCanScroll;	// スクロール可能か否か

	const static D3DXVECTOR2	m_SpreadRange_min;	// 背景の広がる大きさ(最小値)
	const static D3DXVECTOR2	m_SpreadRange_max;	// 背景の広がる大きさ(最大値)
};


#endif // !_BG_H

