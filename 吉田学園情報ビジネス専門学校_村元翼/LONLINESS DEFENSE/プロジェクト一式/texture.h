//=============================================================================
//
// テクスチャ処理 [texture.h]
// Author : 
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTexture
{
public:
	CTexture();			// デフォルトコンストラクタ
	~CTexture();		// デフォルトデストラクタ

	typedef enum
	{
		None = -1,		// テクスチャ無し
		Prov,			// 仮テクスチャ
		Bg,				// 背景
		Title,			// タイトル画面
		Result,			// リザルト画面
		Player,			// プレイヤー
		Enemy,			// 敵
		Bullet,			// 弾
		Number,			// 数字
		Effect,			// エフェクト
		Target,			// ターゲット
		Explosion,		// 爆発
		Gauge,			// ゲージ
		GaugeFrame,		// ゲージフレーム
		MapFrame,		// ミニマップの枠
		Rank1,			// 1位テクスチャ
		Rank2,			// 2位テクスチャ
		Rank3,			// 3位テクスチャ
		Rank4,			// 4位テクスチャ
		Rank5,			// 5位テクスチャ
		GameBack,		// ゲームに戻る
		Retry,			// リトライ
		TitleBack,		// タイトルに戻る
		Cursol,			// カーソル
		PressEnter,		// プレスエンター
		Tutorial01,		// チュートリアル1
		Tutorial02,		// チュートリアル2
		Max,			// テクスチャの最大数
	} Type;

	void Init(void);	// テクスチャの生成
	void Uninit(void);	// 終了
	LPDIRECT3DTEXTURE9 GetTexture(Type Type) { return m_pTexture[Type]; }	// テクスチャの割り当て(テクスチャの種類) { return 選んだテクスチャを返す }

private:
	LPDIRECT3DTEXTURE9	m_pTexture[Max];	// テクスチャ
};

#endif