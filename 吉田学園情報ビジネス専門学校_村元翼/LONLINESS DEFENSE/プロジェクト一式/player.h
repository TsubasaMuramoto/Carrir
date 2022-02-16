//=============================================================================
//
// プレイヤーの処理
// Author : 村元翼
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "scene2D.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CTexture;
class CBullet;
class CXInput;

//=============================================================================
// クラスの生成
//=============================================================================
class CPlayer : public CScene2D
{
public:

	CPlayer(OBJTYPE nPriority = OBJTYPE_PLAYER);		// コンストラクタ
	~CPlayer();											// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, CTexture::Type texture = CTexture::Player);

	void Move(void);
	void MovingLimit(D3DXVECTOR3& pos, D3DXVECTOR3 &scale, D3DXVECTOR3 &speed);
	void Rotate(D3DXVECTOR3 pos, D3DXVECTOR3 scale, float Angle);
	void Acceleration(D3DXVECTOR3& vec, D3DXVECTOR3 speed, float Maxspeed);
	float RotateGamePad(CXInput *pGamePad);
	float FeaturedMouse(D3DXVECTOR3 pos, POINT mousePoint);

	// セッターとゲッター
	void SetPos(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void)			{ return m_pos; }
	D3DXVECTOR3 GetScale(void)			{ return m_scale; }
	D3DXVECTOR3 GetSpeed(void)			{ return m_Speed; }


private:
	D3DXVECTOR3			m_pos;				// 位置
	D3DXVECTOR3			m_scale;			// 大きさ
	D3DXVECTOR3			m_rot;				// 回転
	D3DXVECTOR3			m_velocity;			// posを動かす変数
	D3DXVECTOR3			m_Direction;		// 向き
	D3DXVECTOR3			m_Speed;			// 速度
	D3DXVECTOR3			m_RotateVertex[4];	// 回転に使う頂点座標
	CTexture::Type		m_Tex;				// テクスチャ
	float				m_fMaxSpeed;		// 最高速度
	float				m_fAngle;			// 角度
	float				m_fShootInterval;	// 射撃間隔
	POINT				m_Point;			// カーソル情報

	const static D3DXVECTOR2 m_ScrollRange;
	const static D3DXVECTOR2 m_ScrollRange2;
};

#endif // _PLAYER_H_
