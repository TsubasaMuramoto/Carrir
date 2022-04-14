//=============================================================================
//
// プレイヤー
// Author : 村元翼
//
//=============================================================================
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "keyboard.h"
#include "bullet.h"
#include "effect.h"
#include "mouse.h"
#include "XInput.h"
#include "bg.h"
#include "game.h"
#include "sound.h"
#include <assert.h>

//=============================================================================
// 静的メンバ変数の初期化
//=============================================================================
const D3DXVECTOR2 CPlayer::m_ScrollRange = D3DXVECTOR2(200.0f, 100.0f);
const D3DXVECTOR2 CPlayer::m_ScrollRange2 = D3DXVECTOR2(1080.0f, 620.0f);

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(OBJTYPE nPriority) : CScene2D(nPriority)
{
	m_pos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_rot				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転
	m_scale				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 大きさ
	m_velocity			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 実際の速度
	m_Direction			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	m_Speed				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 速度
	m_fMaxSpeed			= MAX_SPEED;						// 最大速度
	m_fAngle			= 0.0f;								// 角度
	m_fShootInterval	= 0.0f;								// 射撃間隔
	m_RotateVertex[0]	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RotateVertex[1]	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RotateVertex[2]	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RotateVertex[3]	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}

//------------------------------------------------------------
// 頂点座標の設定
//------------------------------------------------------------
void CPlayer::SetPos(D3DXVECTOR3 pos)
{
	CScene::SetPos(pos);

	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// バッファの生成
	pVtx[0].pos = D3DXVECTOR3(pos.x - m_scale.x, pos.y - m_scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + m_scale.x, pos.y - m_scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - m_scale.x, pos.y + m_scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + m_scale.x, pos.y + m_scale.y, 0.0f);

	m_pVtxBuff->Unlock();
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CPlayer::Init(void)
{
	CScene2D::BindTexture(m_Tex);
	CScene2D::Init();
	CScene2D::SetPos(m_pos, m_scale);
	CScene2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CPlayer::Update(void)
{
	CXInput *pGamePad = CManager::GetXInput();
	CMouse *pMouse = CManager::GetMouse();

	CScene2D::Update();
	CScene::SetMove(m_Speed);
	CScene2D::SetPos(m_pos,m_scale,&m_RotateVertex[0]);
	Move();		// プレイヤーの移動

	//==========================================================================================================
	// 弾の発射
	//==========================================================================================================
	if (m_fShootInterval > 0.0f)
	{
		m_fShootInterval -= 0.1f;		// 次に弾が打てるまでのインターバルを減らす
		pGamePad->SetVibration(0,0);	// 振動停止
	}

	else
	{
		// マウスクリックorゲームパッドR2
		if (pMouse->GetPress(pMouse->MOUSE_LEFT) || pGamePad->GetGamePad()->m_state.Gamepad.bRightTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			CBullet::Create(m_pos, BULLET_SIZE, m_fAngle);						// 弾を生成
			m_fShootInterval = SHOOT_INTERVAL;									// 弾のインターバルを設定する
			pGamePad->SetVibration(VIBRATION_POWER_MAX, VIBRATION_POWER_MAX);	// コントローラ振動
		}
	}
}

//=============================================================================
// 描画
//=============================================================================
void CPlayer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスのポインタ

	// アルファブレンド
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);

	CScene2D::Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
}

//=============================================================================
// プレイヤーの生成
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, CTexture::Type texture)
{
	// インスタンス生成
	CPlayer *pPlayer = nullptr;

	if (pPlayer == nullptr)
	{
		pPlayer = new CPlayer(OBJTYPE_PLAYER);

		if (pPlayer != nullptr)
		{
			// プレイヤー情報の取得
			pPlayer->m_pos = pos;
			pPlayer->m_scale = scale;
			pPlayer->m_Tex = texture;

			// 初期化処理
			pPlayer->Init();
		}
	}
	return pPlayer;
}

//=============================================================================
// プレイヤーの移動
//=============================================================================
void CPlayer::Move(void)
{
	// ゲームパッドが接続されているか
	CXInput *pXInput = CManager::GetXInput();
	XINPUT_STATE state;
	DWORD IsConnected = XInputGetState(0, &state);
	if (IsConnected == ERROR_SUCCESS)
	{
		m_fAngle = RotateGamePad(pXInput);			// ゲームパッド入力での角度を求める処理
	}
	else
	{
		m_fAngle = FeaturedMouse(m_pos, m_Point);	// マウスカーソルにプレイヤーが向く処理
	}

	//=============================================================================
	// プレイヤーの移動を決める
	//=============================================================================
	// 前に進む
	if (InputDirection(DIRECTION_UP))
	{
		m_Direction.y = 1.0f;
		m_Speed.y -= 0.2f;
	}

	// 後ろに進む
	else if (InputDirection(DIRECTION_DOWN))
	{
		m_Direction.y = 1.0f;
		m_Speed.y += 0.2f;
	}

	// 前後押していない状態
	else if (InputDirection(DIRECTION_NO_UP) && InputDirection(DIRECTION_NO_DOWN))
	{
		m_Direction.y = 0.0f;
	}

	// 右に進む
	if (InputDirection(DIRECTION_RIGHT))
	{
		m_Direction.x = 1.0f;
		m_Speed.x += 0.2f;
	}

	// 左に進む
	else if (InputDirection(DIRECTION_LEFT))
	{
		m_Direction.x = -1.0f;
		m_Speed.x -= 0.2f;
	}

	// 左右押していない状態
	else if (InputDirection(DIRECTION_NO_LEFT) && InputDirection(DIRECTION_NO_RIGHT))
	{
		m_Direction.x = 0.0f;
	}

	//==========================================================================================================
	// 移動する(座標更新)
	//==========================================================================================================
	m_pos.x += m_Speed.x;
	m_pos.y += m_Speed.y;

	//==========================================================================================================
	// エフェクト生成とモーター振動
	//==========================================================================================================
	if (InputDirection(DIRECTION_UP) || InputDirection(DIRECTION_DOWN) ||
		InputDirection(DIRECTION_LEFT) || InputDirection(DIRECTION_RIGHT))
	{
		// 振動させる
		pXInput->SetVibration(VIBRATION_POWER_RIGHT, VIBRATION_POWER_LEFT);

		// エフェクト生成
		CEffect::Create(m_pos, m_Speed, m_scale, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.5f,0.01f, m_fAngle,CEffect::EFFECT_PLAYER);
	}

	else
	{
		// モーターの力を0にする(振動を停止)
		pXInput->SetVibration(0, 0);
	}

	//==========================================================================================================
	// 移動に使う関数
	//==========================================================================================================
	GetCursorPos(&m_Point);									// マウスカーソル座標の取得(スクリーン座標)
	ScreenToClient(CRenderer::GethWnd(), &m_Point);			// マウスのスクリーン座標をクライアント座標に変換
	Acceleration(m_velocity, m_Speed, m_fMaxSpeed);			// 慣性
	Rotate(m_pos, m_scale, m_fAngle);						// 回転
	MovingLimit(m_pos, m_scale, m_Speed);					// 移動限界

}

//=============================================================================
// プレイヤーの慣性
//=============================================================================
void CPlayer::Acceleration(D3DXVECTOR3& velo, D3DXVECTOR3& speed,const float &Maxspeed)
{
	m_velocity = velo;
	m_Speed = speed;
	m_fMaxSpeed = Maxspeed;

	//------------------------------------------------
	// 左右入力していない状態
	//------------------------------------------------
	if (m_Direction.x == 0.0f)
	{
		// 0に戻り続ける処理
		if (m_Speed.x > 0.0f)
		{
			m_Speed.x -= INERTIA_SPEED;

			if (m_Speed.x <= 0.0f)
			{
				m_Speed.x = 0.0f;
			}
		}

		else if (m_Speed.x < 0.0f)
		{
			m_Speed.x += INERTIA_SPEED;

			if (m_Speed.x >= 0.0f)
			{
				m_Speed.x = 0.0f;
			}
		}
	}

	//------------------------------------------------
	// 上下入力していない状態
	//------------------------------------------------
	if (m_Direction.y == 0.0f)
	{
		// 0に戻り続ける処理
		if (m_Speed.y > 0.0f)
		{
			m_Speed.y -= INERTIA_SPEED;

			if (m_Speed.y <= 0.0f)
			{
				m_Speed.y = 0.0f;
			}
		}

		else if (m_Speed.y < 0.0f)
		{
			m_Speed.y += INERTIA_SPEED;

			if (m_Speed.y >= 0.0f)
			{
				m_Speed.y = 0.0f;
			}
		}
	}

	//------------------------------------------------
	// 最大スピード
	//------------------------------------------------
	if (m_Speed.x >= m_fMaxSpeed)
	{
		m_Speed.x = m_fMaxSpeed;
	}

	else if (m_Speed.x <= -m_fMaxSpeed)
	{
		m_Speed.x = -m_fMaxSpeed;
	}

	if (m_Speed.y >= m_fMaxSpeed)
	{
		m_Speed.y = m_fMaxSpeed;
	}

	else if (m_Speed.y <= -m_fMaxSpeed)
	{
		m_Speed.y = -m_fMaxSpeed;
	}

	// 右移動は＋方向、左移動は－方向、押さなかったら0
	m_velocity = m_Speed;
}

//=============================================================================
// 向きの回転を行う関数
//=============================================================================
void CPlayer::Rotate(D3DXVECTOR3 pos, D3DXVECTOR3 scale, float Angle)
{
	D3DXVECTOR3 vertex[4];

	// 4頂点の設定
	vertex[0] = D3DXVECTOR3(-scale.x / 2, -scale.y / 2, 0.0f);
	vertex[1] = D3DXVECTOR3(+scale.x / 2, -scale.y / 2, 0.0f);
	vertex[2] = D3DXVECTOR3(-scale.x / 2, +scale.y / 2, 0.0f);
	vertex[3] = D3DXVECTOR3(+scale.x / 2, +scale.y / 2, 0.0f);
	
	for (int nCnt = 0; nCnt < VTX_NUM2D; nCnt++)
	{
		float x = vertex[nCnt].x;
		float y = vertex[nCnt].y;

		m_RotateVertex[nCnt].x = x * cosf(Angle) - y * sinf(Angle);
		m_RotateVertex[nCnt].y = x * sinf(Angle) + y * cosf(Angle);
	}
}

//=============================================================================
// 移動限界に到達した時の関数
//=============================================================================
void CPlayer::MovingLimit(D3DXVECTOR3 &pos, D3DXVECTOR3 &scale, D3DXVECTOR3 &speed)
{
	// スクロールし始める範囲(横)
	if (pos.x + (scale.x / 2) >= m_ScrollRange2.x || pos.x - (scale.x / 2) <= m_ScrollRange.x)
	{
		// 右スクロールをする範囲
		if (pos.x + (scale.x / 2) >= m_ScrollRange2.x)
		{
			if (CGame::GetBg()->GetPos().x >= CBg::GetRangeMax().x)		// 背景が一番右に行ったとき
			{
				// ウィンドウの右端までプレイヤーが行く
				if (pos.x + (scale.x / 2) > SCREEN_WIDTH)
				{
					pos.x = SCREEN_WIDTH - (scale.x / 2);				// プレイヤー位置をウィンドウ範囲内に戻す
					speed.x = 0.0f;
				}

				CGame::SetScroll("StopX", speed);
			}

			else
			{
				pos.x = m_ScrollRange2.x - (scale.x / 2);				// プレイヤー位置をスクロール範囲内に戻す
				CGame::SetScroll("X", speed);							// スクロールを設定する
			}
		}

		// 左スクロールをする範囲
		if (pos.x - (scale.x / 2) <= m_ScrollRange.x)
		{
			if (CGame::GetBg()->GetPos().x <= CBg::GetRangeMin().x)	// 左
			{
				// ウィンドウの左端までプレイヤーが行く
				if (pos.x - (scale.x / 2) < 0.0f)
				{
					pos.x = (scale.x / 2);
					speed.x = 0.0f;
				}

				CGame::SetScroll("StopX", speed);
			}

			else
			{
				pos.x = m_ScrollRange.x + (scale.x / 2);
				CGame::SetScroll("X", speed);
			}
		}
	}

	else
	{
		CGame::SetScroll("StopX", speed);						// 横スクロールをストップ
	}

	// スクロールし始める範囲(縦)
	if (pos.y + (scale.y / 2) >= m_ScrollRange2.y || pos.y - (scale.y / 2) <= m_ScrollRange.y)
	{
		// 下スクロール範囲まで行ったら
		if (pos.y + (scale.y / 2) >= m_ScrollRange2.y)
		{
			if (CGame::GetBg()->GetPos().y >= CBg::CBg::GetRangeMax().y)	// 背景下限界まで行ったとき
			{
				// ウィンドウの下端までプレイヤーが行く
				if (pos.y + (scale.y / 2) > SCREEN_HEIGHT)
				{
					pos.y = SCREEN_HEIGHT - (scale.y / 2);
					speed.y = 0.0f;
				}

				CGame::SetScroll("StopY", speed);
			}

			else
			{
				pos.y = m_ScrollRange2.y - (scale.y / 2);
				CGame::SetScroll("Y", speed);
			}
		}

		// 上スクロール範囲まで行ったら
		if (pos.y - (scale.y / 2) <= m_ScrollRange.y)
		{
			if (CGame::GetBg()->GetPos().y <= CBg::CBg::GetRangeMin().y)	// 上
			{
				// ウィンドウの上端までプレイヤーが行く
				if (pos.y - (scale.y / 2) < 0.0f)
				{
					pos.y = (scale.y / 2);
					speed.y = 0.0f;
				}

				CGame::SetScroll("StopY", speed);
			}

			else
			{
				pos.y = m_ScrollRange.y + (scale.y / 2);
				CGame::SetScroll("Y", speed);
			}
		}
	}

	else
	{
		CGame::SetScroll("StopY", speed);			// 縦スクロールをストップ
	}

}

//=============================================================================
// マウスカーソルの位置に角度が向く関数
//=============================================================================
float CPlayer::FeaturedMouse(D3DXVECTOR3 pos, POINT mousePoint)
{
	// オブジェクトの位置とマウスカーソルの位置の差分を求める
	const float fLengthX = (pos.x - mousePoint.x);
	const float fLengthY = (pos.y - mousePoint.y);

	// 角度を求める(XYを逆にして引数に入れると↑から0度になる)
	const float fAngle = -atan2f(fLengthX, fLengthY);

	return fAngle;
}

//=============================================================================
// ゲームパッドで回転を行う関数
//=============================================================================
float CPlayer::RotateGamePad(CXInput *pXInput)
{
	if (pXInput->GetGamePad()->m_state.Gamepad.sThumbRX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		pXInput->GetGamePad()->m_state.Gamepad.sThumbRX <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		pXInput->GetGamePad()->m_state.Gamepad.sThumbRY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		pXInput->GetGamePad()->m_state.Gamepad.sThumbRY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		const float RX = pXInput->GetGamePad()->m_state.Gamepad.sThumbRX;
		const float RY = pXInput->GetGamePad()->m_state.Gamepad.sThumbRY;

		const float magnitude = sqrtf(RX*RX + RY*RY);

		const float normalizedRX = RX / magnitude;
		const float normalizedRY = RY / magnitude;

		// 角度を求める(XYを逆にして引数に入れると↑から0度になる)
		const float fAngle = atan2f(normalizedRX, normalizedRY);
		return fAngle;
	}

	else
	{
		return m_fAngle;
	}
}

//=============================================================================
// 入力方向
//=============================================================================
bool CPlayer::InputDirection(const MOVE_DIRECTION &moveDir)
{
	CXInput *pXInput = CManager::GetXInput();
	CInputkeyboard *pKey = CManager::GetKeyboard();

	switch (moveDir)
	{
	case DIRECTION_UP:
		return pKey->GetPress(DIK_W) || pXInput->GetGamePad()->m_state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

	case DIRECTION_DOWN:
		return pKey->GetPress(DIK_S) || pXInput->GetGamePad()->m_state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

	case DIRECTION_LEFT:
		return pKey->GetPress(DIK_A) || pXInput->GetGamePad()->m_state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

	case DIRECTION_RIGHT:
		return pKey->GetPress(DIK_D) || pXInput->GetGamePad()->m_state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

	case DIRECTION_NO_UP:
		return !pKey->GetPress(DIK_W) || pXInput->GetGamePad()->m_state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

	case DIRECTION_NO_DOWN:
		return !pKey->GetPress(DIK_S) || pXInput->GetGamePad()->m_state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

	case DIRECTION_NO_LEFT:
		return !pKey->GetPress(DIK_A) || pXInput->GetGamePad()->m_state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

	case DIRECTION_NO_RIGHT:
		return !pKey->GetPress(DIK_D) || pXInput->GetGamePad()->m_state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

	default:
		assert(moveDir <= -1 || moveDir >= DIRECTION_MAX);
		return false;
	}
}

