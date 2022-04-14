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
// マクロ定義
//=============================================================================
#define MAX_SPEED		(10.0f)														// 最大速度
#define SHOOT_INTERVAL	(0.5f)														// 弾発射間隔
#define INERTIA_SPEED	(0.2f)														// 慣性速度(加速and減速)
#define PLAYER_POS		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))	// プレイヤー位置
#define PLAYER_SIZE		(D3DXVECTOR3(40.0f, 40.0f, 0.0f))							// プレイヤーサイズ

//=============================================================================
// 前方宣言
//=============================================================================
class CXInput;

//=============================================================================
// クラスの生成
//=============================================================================
class CPlayer : public CScene2D
{
public:

	// 移動方向
	typedef enum
	{
		DIRECTION_UP = 0,	// 上
		DIRECTION_DOWN,		// 下
		DIRECTION_LEFT,		// 左
		DIRECTION_RIGHT,	// 右
		DIRECTION_NO_UP,	// 上無
		DIRECTION_NO_DOWN,	// 下無
		DIRECTION_NO_LEFT,	// 左無
		DIRECTION_NO_RIGHT,	// 右無
		DIRECTION_MAX

	}MOVE_DIRECTION;


	CPlayer(OBJTYPE nPriority = OBJTYPE_PLAYER);		// コンストラクタ
	~CPlayer();											// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, CTexture::Type texture = CTexture::Player);

	void Move(void);																// プレイヤーの移動関数
	void MovingLimit(D3DXVECTOR3& pos, D3DXVECTOR3 &scale, D3DXVECTOR3 &speed);		// 移動限界設定関数
	void Rotate(D3DXVECTOR3 pos, D3DXVECTOR3 scale, float Angle);					// 回転関数
	void Acceleration(D3DXVECTOR3 &velo, D3DXVECTOR3 &speed,const float &Maxspeed);	// 慣性関数
	float RotateGamePad(CXInput *pXInput);											// ゲームパッドでの回転関数
	float FeaturedMouse(D3DXVECTOR3 pos, POINT mousePoint);							// マウス追従処理関数
	bool InputDirection(const MOVE_DIRECTION &moveDir);							// 移動方向入力関数

	//-------------------------
	// Getter & Setter
	//-------------------------
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

	const static D3DXVECTOR2 m_ScrollRange;	// スクロールレンジ
	const static D3DXVECTOR2 m_ScrollRange2;// スクロールレンジ
};

#endif // _PLAYER_H_
