//--------------------------------------------------
// エフェクトの作成
// Author
//--------------------------------------------------
#ifndef _EFFECT_H_
#define _EFFECT_H_
#include "texture.h"
#include "scene.h"
#include "scene2D.h"

//---------------------------------------------------------------
// 前方宣言
//---------------------------------------------------------------

//---------------------------------------------------------------
// エフェクトクラス(シーン2Dの派生)
//---------------------------------------------------------------
class CEffect : public CScene2D
{
public:

	//-------------------------------------------
	// エフェクトタイプ構造体
	//-------------------------------------------
	typedef enum
	{
		EFFECT_NORMAL = 0,	// 普通
		EFFECT_BULLET,		// 弾
		EFFECT_PLAYER,		// プレイヤー
		EFFECT_EXPLOSION,	// 爆発
		EFFECT_MAX			// 最大

	}EFFECT_TYPE;

	CEffect(OBJTYPE OBJTYPE_EFFECT);
	~CEffect();

	HRESULT Init(CTexture::Type type);
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	/* 位置の設定,移動量,サイズ,色設定,小さくなるスピード,Texture */
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 m_move, D3DXVECTOR3 size, D3DXCOLOR col, float ScaleSpeed, float TransparentSpeed, float angle, EFFECT_TYPE effectType, CTexture::Type type = CTexture::Effect);
	void ProcessByType(EFFECT_TYPE type);
	void RandomInjection(void);									// ある方向にランダム噴射するエフェクト
	void EffectAnim(int &nAnimCounter, int nSpan, D3DXVECTOR2 &Pattern,D3DXVECTOR2 MaxPattern);

private:

	EFFECT_TYPE		m_EffectType;			// エフェクトタイプ
	D3DXVECTOR3		m_pos;					// 位置
	D3DXVECTOR3		m_posOld;				// 最後の位置
	D3DXVECTOR3		m_move;					// 移動量
	D3DXVECTOR3		m_size;					// 大きさ
	D3DXCOLOR		m_col;					// 色
	D3DXVECTOR2		m_Pattern;				// アニメーションパターン
	int				m_nAnimCounter;			// アニメーションカウンター
	int				m_nLife;				// 寿命
	float			m_fAngle;				// 角度
	float			m_fScaleSpeed;			// サイズを小さくする速度
	float			m_fTransparentSpeed;	// 透過する速度
	bool			m_bDoOnce;				// 一度だけ通す判定
	bool			m_bUse;					// 使用判定

};
#endif // !_EFFECT_H_

