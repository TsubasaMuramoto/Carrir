//=============================================================================
//
// テクスチャ処理 [texture.cpp]
//
//=============================================================================
#include "texture.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CTexture::CTexture()
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
// テクスチャの生成
//=============================================================================
void CTexture::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;							// デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();		// デバイスを取得する

	D3DXCreateTextureFromFile
	(
		pDevice,
		"",									// 無し
		&m_pTexture[None]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Flag.png",			// 仮
		&m_pTexture[Prov]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Player.png",			// プレイヤー
		&m_pTexture[Player]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Bullet.png",			// 弾
		&m_pTexture[Bullet]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Enemy.png",			// 敵
		&m_pTexture[Enemy]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Bg.jpg",				// 背景
		&m_pTexture[Bg]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/title.png",			// タイトル画面
		&m_pTexture[Title]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Bg.jpg",				// リザルト画面
		&m_pTexture[Result]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/number000.png",		// ナンバー
		&m_pTexture[Number]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Effect000.jpg",		// エフェクト
		&m_pTexture[Effect]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Earth.png",			// ターゲット
		&m_pTexture[Target]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Explosion003.png",	// 爆発
		&m_pTexture[Explosion]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Gauge000.png",		// ゲージ
		&m_pTexture[Gauge]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/GaugeFrame000.png",	// ゲージフレーム
		&m_pTexture[GaugeFrame]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/MapFrame001.png",		// マップフレーム
		&m_pTexture[MapFrame]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/1st.png",				// 1位
		&m_pTexture[Rank1]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/2nd.png",				// 2位
		&m_pTexture[Rank2]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/3rd.png",				// 3位
		&m_pTexture[Rank3]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/4th.png",				// 4位
		&m_pTexture[Rank4]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/5th.png",				// 5位
		&m_pTexture[Rank5]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/ReturnGame.png",		// ゲームに戻る
		&m_pTexture[GameBack]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Retry.png",			// リトライ
		&m_pTexture[Retry]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/ReturnTitle.png",		// タイトルに戻る
		&m_pTexture[TitleBack]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/right.png",			// カーソル
		&m_pTexture[Cursol]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/press.png",			// プレスエンター
		&m_pTexture[PressEnter]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Tutorial001.png",		// チュートリアル1
		&m_pTexture[Tutorial01]
	);

	D3DXCreateTextureFromFile
	(
		pDevice,
		"data/TEXTURE/Tutorial002.png",		// チュートリアル2
		&m_pTexture[Tutorial02]
	);
}

//=============================================================================
// 終了
//=============================================================================
void CTexture::Uninit(void)
{
	for (int nCntTexture = 0; nCntTexture < Max; nCntTexture++)
	{
		//テクスチャの破棄
		if (m_pTexture[nCntTexture] != nullptr)
		{
			m_pTexture[nCntTexture]->Release();
			m_pTexture[nCntTexture] = nullptr;
		}
	}
}