//----------------------------------
// ポリゴンの処理
//----------------------------------
#ifndef _SCENE2D_H
#define _SCENE2D_H
#include "main.h"
#include "scene.h"
#include "texture.h"

//----------------------------------
// マクロ定義
//----------------------------------
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;//頂点座標
	float		rhw;//1.0fで固定
	D3DCOLOR	col;//頂点カラー
	D3DXVECTOR2 tex;//テクスチャ座標
} VERTEX_2D;

//------------------------------------------------------------------------------
// クラスの定義
//------------------------------------------------------------------------------
class CScene2D : public CScene
{
public:
	CScene2D(OBJTYPE nPriority = OBJTYPE_NONE);
	~CScene2D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CTexture::Type texture = CTexture::Prov,CScene::OBJTYPE objtype = CScene::OBJTYPE_NONE);

	//------------------------------------------------------------------------------
	// Setter
	//------------------------------------------------------------------------------
	void SetScalePos(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void SetPos(D3DXVECTOR3 vtx0, D3DXVECTOR3 vtx1, D3DXVECTOR3 vtx2, D3DXVECTOR3 vtx3);	
	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale,bool bScroll = true);
	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 Rotvtx0, D3DXVECTOR3 Rotvtx1, D3DXVECTOR3 Rotvtx2, D3DXVECTOR3 Rotvtx3);

	void SetTex(int nAnim,int nPartU);															// テクスチャの取得
	void SetTex(float fSpeedX, float fSpeedY);													// テクスチャの設定
	void SetTex(float nPatternX, float nPatternY, float fSizeX,float fSizeY);					// テクスチャの設定

	void SetCol(D3DXCOLOR col);																	// カラーの設定
	static D3DXVECTOR3 Move(D3DXVECTOR3 *pPos, float angle, float speed);						// 移動関数
	void BindTexture(CTexture::Type type);														// テクスチャ取得関数

private:
	bool m_bUse;											// 使用状況

protected:

	LPDIRECT3DTEXTURE9		m_pTexture = NULL;				// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;				// 頂点バッファへのポインタ

};


#endif // !_SCENE2D_H
