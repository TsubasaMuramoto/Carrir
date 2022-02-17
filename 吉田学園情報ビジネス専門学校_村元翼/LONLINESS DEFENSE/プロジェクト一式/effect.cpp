//--------------------------------------------------
// エフェクトの作成
// Author : 村元翼
//--------------------------------------------------
#include "main.h"
#include "effect.h"
#include "manager.h"
#include "renderer.h"
#include "bullet.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CEffect::CEffect(OBJTYPE nPriority) : CScene2D(nPriority)
{
	m_fAngle = 0.0f;
	m_fScaleSpeed = 0.0f;
	m_nAnimCounter = 0;
	m_Pattern = D3DXVECTOR2(0.0f, 0.0f);
	m_bDoOnce = false;
	m_bUse = false;
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEffect::~CEffect()
{

}

//---------------------------------------------------
// エフェクト生成
//---------------------------------------------------
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, D3DXCOLOR col,float ScaleSpeed, float TransparentSpeed, float angle, EFFECT_TYPE effectType,CTexture::Type type)
{//	位置, 移動量, サイズ,色, 小さくなるスピード

	// インスタンス生成
	CEffect *pEffect = nullptr;
	if (pEffect == nullptr)
	{
		pEffect = new CEffect(OBJTYPE_EFFECT);

		if (pEffect != nullptr)
		{
			// 引数代入
			pEffect->m_pos = pos;
			pEffect->m_move = move;
			pEffect->m_size = size;
			pEffect->m_col = col;
			pEffect->m_fScaleSpeed = ScaleSpeed;
			pEffect->m_fTransparentSpeed = TransparentSpeed;
			pEffect->m_fAngle = angle;
			pEffect->m_EffectType = effectType;
			pEffect->m_bUse = true;
			pEffect->Init(type);								// 画像読み込み
		}
	}

	return pEffect;
}

//----------------------------------------------------
// 初期化処理
//-----------------------------------------------------
HRESULT CEffect::Init(CTexture::Type type)
{
	CScene2D::BindTexture(type);
	CScene2D::Init();
	CScene2D::SetPos(m_pos, m_size);
	CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

HRESULT CEffect::Init()
{
	return S_OK;
}

//---------------------------------------------------------
// 終了処理
//---------------------------------------------------------
void CEffect::Uninit()
{
	m_bUse = false;
	CScene2D::Uninit();
}

//----------------------------------------------------
// 更新
//-----------------------------------------------------
void CEffect::Update()
{
	if (m_bUse == true)
	{
		CScene2D::SetPos(m_pos, m_size);	// 頂点情報の設定(更新)
		CScene2D::SetCol(m_col);			// カラーの設定(更新)
		m_pos = CScene::GetPos();			// 位置の取得

		ProcessByType(m_EffectType);		// タイプ別エフェクト処理

		// XとYのサイズが0になったら消す
		if (m_size.x <= 0 && m_size.y <= 0)
		{
			Uninit();
		}

		//α値が0以下になったら消える
		if (m_col.a <= 0.0)
		{
			Uninit();
		}
	}
}

//----------------------------------------------------
// 描画
//-----------------------------------------------------
void CEffect::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスのポインタ

	// 加算合成の設定
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	// 元の設定に戻す
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//----------------------------------------------------
// エフェクトタイプ別処理
//-----------------------------------------------------
void CEffect::ProcessByType(EFFECT_TYPE type)
{
	//---------------------------------------------------
	// 一度だけ行う処理
	//---------------------------------------------------
	if (m_bDoOnce == false)
	{
		switch (type)
		{
		case EFFECT_BULLET:
			break;

		case EFFECT_PLAYER:
			RandomInjection();
			break;

		case EFFECT_EXPLOSION:
			break;
		}
		m_bDoOnce = true;
	}

	//---------------------------------------------------
	// 繰り返す処理
	//---------------------------------------------------
	switch (type)
	{
	case EFFECT_BULLET:
		CScene2D::Move(&m_pos, m_fAngle, m_move.x);	
		//m_col.a -= m_fTransparentSpeed;	// 明るさを下げる
		break;

	case EFFECT_PLAYER:
		CScene2D::Move(&m_pos, m_fAngle, 2.0f);
		break;

	case EFFECT_EXPLOSION:
		CScene2D::SetTex(m_Pattern.x, m_Pattern.y, 0.2f, 0.5f);
		EffectAnim(m_nAnimCounter, 3, m_Pattern, D3DXVECTOR2(5.0f,2.0f));
		break;
	}

	// エフェクトが小さくなっていく処理
	m_size.x -= m_fScaleSpeed;
	m_size.y -= m_fScaleSpeed;
}

//----------------------------------------------------
// 一方向にランダムに噴射するエフェクトの処理
//-----------------------------------------------------
void CEffect::RandomInjection(void)
{
	// 噴射エフェクトの角度幅の最小値と次第値
	float minRange = D3DXToRadian(-90.0f);
	float maxRange = D3DXToRadian(90.0f);

	std::random_device Randseed;												// 乱数生成器でシード値を完全ランダムに初期化する
	std::mt19937_64 mt(Randseed());												// 疑似乱数を作り出す
	std::uniform_real_distribution<float> Dist(minRange, maxRange);				// 指定した範囲内の数値を等確率で返す(最小値以上、最大値"未満")

	m_fAngle = Dist(mt);

#if _DEBUG_
	float fDegree = D3DXToDegree(m_fAngle);										// デバッグ時に角度を確認するための処理
#endif

	if (m_move.x != 0.0f)		// 左右
	{
		m_fAngle += D3DXToRadian(-90.0f);
	}
}

//----------------------------------------------------
// エフェクトのアニメーション
//-----------------------------------------------------
void CEffect::EffectAnim(int &nAnimCounter, int nSpan, D3DXVECTOR2 &Pattern, D3DXVECTOR2 MaxPattern)
{
	nAnimCounter++;						// カウンターを進める

	if (nAnimCounter >= nSpan)			// カウンター超える
	{
		nAnimCounter = 0;
		Pattern.x++;
	}

	if (Pattern.x >= MaxPattern.x)		// アニメーションパターンX軸最大
	{
		Pattern.x = 0;
		Pattern.y++;
	}

	if (Pattern.y >= MaxPattern.y)		// アニメーションパターンY軸最大
	{
		Pattern.y = 0;
		Uninit();
	}
}
