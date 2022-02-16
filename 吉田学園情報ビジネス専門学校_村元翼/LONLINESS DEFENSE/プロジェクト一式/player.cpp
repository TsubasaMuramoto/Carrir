//=============================================================================
//
// プレイヤー
// Author : 村元翼
//
//=============================================================================
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "keyboard.h"
#include "bullet.h"
#include "effect.h"
#include "mouse.h"
#include "XInput.h"
#include "bg.h"
#include "game.h"

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
	m_fMaxSpeed			= 0.0f;								// 最大速度
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

	CScene2D::Update();
	CScene::SetMove(m_Speed);
	CScene2D::SetPos(m_pos,m_scale,m_RotateVertex[0],m_RotateVertex[1],m_RotateVertex[2],m_RotateVertex[3]);
	Move();		// プレイヤーの移動

	//==========================================================================================================
	// 弾の発射
	//==========================================================================================================
	if (m_fShootInterval > 0.0f)
	{
		m_fShootInterval -= 0.1f;	// 次に弾が打てるまでのインターバルを減らす

		
		pGamePad->m_GamePad.m_vibration.wLeftMotorSpeed = 0;
		pGamePad->m_GamePad.m_vibration.wRightMotorSpeed = 0;
		XInputSetState(0, &pGamePad->m_GamePad.m_vibration);
	}

	else
	{
		// マウスクリックorゲームパッドR2
		if (CManager::GetMouse()->GetPress(CMouse::MOUSE_LEFT) || pGamePad->GetGamePad()->m_state.Gamepad.bRightTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			CBullet::Create(m_pos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), m_fAngle);	// 弾を生成
			m_fShootInterval = 0.5f;											// 弾のインターバルを設定する

			// 振動させる
			pGamePad->m_GamePad.m_vibration.wLeftMotorSpeed = VIBRATION_POWER_MAX;
			pGamePad->m_GamePad.m_vibration.wRightMotorSpeed = VIBRATION_POWER_MAX;
			XInputSetState(0, &pGamePad->m_GamePad.m_vibration);
		}
	}
}

//=============================================================================
// 描画
//=============================================================================
void CPlayer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//デバイスのポインタ

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
	CPlayer *pPlayer = new CPlayer(OBJTYPE_PLAYER);

	// プレイヤー情報の取得
	pPlayer->m_pos = pos;
	pPlayer->m_scale = scale;
	pPlayer->m_Tex = texture;
	pPlayer->m_Direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pPlayer->m_fMaxSpeed = 10.0f;
	pPlayer->m_Speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pPlayer->m_fShootInterval = 0.5f;

	if (pPlayer != NULL)
	{
		// 初期化処理
		pPlayer->Init();
	}

	return pPlayer;
}

//=============================================================================
// プレイヤーの移動
//=============================================================================
void CPlayer::Move(void)
{
	CXInput *pGamePad = CManager::GetXInput();

	// ゲームパッドが接続されているか
	XINPUT_STATE state;
	DWORD IsConnected = XInputGetState(0, &state);
	if (IsConnected == ERROR_SUCCESS)
	{
		m_fAngle = RotateGamePad(pGamePad);						// ゲームパッド入力での角度を求める処理
	}
	else
	{
		m_fAngle = FeaturedMouse(m_pos, m_Point);				// マウスカーソルにプレイヤーが向く処理
	}

	//=============================================================================
	// プレイヤーの移動を決める
	//=============================================================================
	// 前に進む
	if (CManager::GetKeyboard()->GetPress(DIK_W) == true || pGamePad->GetGamePad()->m_state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		m_Direction.y = 1.0f;
		m_Speed.y -= 0.2f;
	}

	// 後ろに進む
	else if (CManager::GetKeyboard()->GetPress(DIK_S) == true || pGamePad->GetGamePad()->m_state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		m_Direction.y = 1.0f;
		m_Speed.y += 0.2f;
	}

	// 前後押していない状態
	else if ((CManager::GetKeyboard()->GetPress(DIK_W) == false && 
			  CManager::GetKeyboard()->GetPress(DIK_S) == false) || 
			 (pGamePad->GetGamePad()->m_state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && 
			  pGamePad->GetGamePad()->m_state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		m_Direction.y = 0.0f;
	}

	// 右に進む
	if (CManager::GetKeyboard()->GetPress(DIK_D) == true || pGamePad->GetGamePad()->m_state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		m_Direction.x = 1.0f;
		m_Speed.x += 0.2f;
	}

	// 左に進む
	else if (CManager::GetKeyboard()->GetPress(DIK_A) == true ||  pGamePad->GetGamePad()->m_state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		m_Direction.x = -1.0f;
		m_Speed.x -= 0.2f;
	}

	// 左右押していない状態
	else if ((CManager::GetKeyboard()->GetPress(DIK_A) == false &&
			  CManager::GetKeyboard()->GetPress(DIK_D) == false) ||
			 (pGamePad->GetGamePad()->m_state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			  pGamePad->GetGamePad()->m_state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
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
	if (CManager::GetKeyboard()->GetPress(DIK_W) == true || CManager::GetKeyboard()->GetPress(DIK_S) == true ||
		CManager::GetKeyboard()->GetPress(DIK_A) == true || CManager::GetKeyboard()->GetPress(DIK_D) == true ||
		pGamePad->GetGamePad()->m_state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		pGamePad->GetGamePad()->m_state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		pGamePad->GetGamePad()->m_state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		pGamePad->GetGamePad()->m_state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
		)
	{
		// 振動させる
		pGamePad->m_GamePad.m_vibration.wLeftMotorSpeed = VIBRATION_POWER_LEFT;
		pGamePad->m_GamePad.m_vibration.wRightMotorSpeed = VIBRATION_POWER_RIGHT;
		XInputSetState(0, &pGamePad->m_GamePad.m_vibration);

		// エフェクト生成
		CEffect::Create(m_pos, m_Speed, m_scale, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.5f,0.01f, m_fAngle,CEffect::EFFECT_PLAYER);
	}

	else
	{
		// モーターの力を0にする(振動を停止)
		pGamePad->m_GamePad.m_vibration.wLeftMotorSpeed = 0;
		pGamePad->m_GamePad.m_vibration.wRightMotorSpeed = 0;
		XInputSetState(0, &pGamePad->m_GamePad.m_vibration);
	}

	//==========================================================================================================
	// 移動に使う関数
	//==========================================================================================================
	GetCursorPos(&m_Point);									// マウスカーソル座標の取得(スクリーン座標)
	ScreenToClient(CRenderer::GethWnd(), &m_Point);			// マウスのスクリーン座標をクライアント座標に変換
	Acceleration(m_velocity, m_Speed, m_fMaxSpeed);			// 慣性
	Rotate(m_pos, m_scale, m_fAngle);						// 回転
	MovingLimit(m_pos, m_scale, m_Speed);					// 移動限界

	/*float length = 0.0f;
	float normal_x = 0.0f;
	float normal_y = 0.0f;*/
	//---------------------------------------------------------------------------------------------
	// 斜め移動を正確にする
	//---------------------------------------------------------------------------------------------
		//// 加速度になにか数値が入っていた場合
		//if (m_velocity.x != 0.0f || m_velocity.y != 0.0f)
		//{
		//	// xの速度とyの速度から斜めの速度を求める
		//	length = sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
		//	// それぞれの長さを斜めの長さで割ってあげる
		//	normal_x = m_velocity.x / length;
		//	normal_y = m_velocity.y / length;
		//	//	速度をかける
		//	normal_x *= m_fSpeed.x;
		//	normal_y *= m_fSpeed.y;
		//	// 移動する(座標更新)
		//	m_pos.x += normal_x;
		//	m_pos.y += normal_y;
		//}

}

//=============================================================================
// プレイヤーの慣性
//=============================================================================
void CPlayer::Acceleration(D3DXVECTOR3& vec, D3DXVECTOR3 speed, float Maxspeed)
{
	m_velocity = vec;
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
			m_Speed.x -= 0.2f;

			if (m_Speed.x <= 0.0f)
			{
				m_Speed.x = 0.0f;
			}
		}

		else if (m_Speed.x < 0.0f)
		{
			m_Speed.x += 0.2f;

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
			m_Speed.y -= 0.2f;

			if (m_Speed.y <= 0.0f)
			{
				m_Speed.y = 0.0f;
			}
		}

		else if (m_Speed.y < 0.0f)
		{
			m_Speed.y += 0.2f;

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

	if (m_Speed.x <= -m_fMaxSpeed)
	{
		m_Speed.x = -m_fMaxSpeed;
	}

	if (m_Speed.y >= m_fMaxSpeed)
	{
		m_Speed.y = m_fMaxSpeed;
	}

	if (m_Speed.y <= -m_fMaxSpeed)
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

	// 4頂点の取得
	vertex[0] = D3DXVECTOR3(-scale.x / 2, -scale.y / 2, 0.0f);
	vertex[1] = D3DXVECTOR3(+scale.x / 2, -scale.y / 2, 0.0f);
	vertex[2] = D3DXVECTOR3(-scale.x / 2, +scale.y / 2, 0.0f);
	vertex[3] = D3DXVECTOR3(+scale.x / 2, +scale.y / 2, 0.0f);
	
	for (int nCnt = 0; nCnt < 4; nCnt++)
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

				CGame::SetScroll("noX", speed);
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

				CGame::SetScroll("noX", speed);
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
		CGame::SetScroll("noX", speed);						// 横スクロールをストップ
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

				CGame::SetScroll("noY", speed);
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

				CGame::SetScroll("noY", speed);
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
		CGame::SetScroll("noY", speed);			// 縦スクロールをストップ
	}

}

//=============================================================================
// マウスカーソルの位置に角度が向く関数
//=============================================================================
float CPlayer::FeaturedMouse(D3DXVECTOR3 pos, POINT mousePoint)
{
	// オブジェクトの位置とマウスカーソルの位置の差分を求める
	float fLengthX = (pos.x - mousePoint.x);
	float fLengthY = (pos.y - mousePoint.y);

	// 角度を求める(XYを逆にして引数に入れると↑から0度になる)
	float fAngle = (float)-atan2(fLengthX, fLengthY);

	return fAngle;
}

//=============================================================================
// ゲームパッドで回転を行う関数
//=============================================================================
float CPlayer::RotateGamePad(CXInput *pGamePad)
{
	if (pGamePad->GetGamePad()->m_state.Gamepad.sThumbRX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		pGamePad->GetGamePad()->m_state.Gamepad.sThumbRX <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		pGamePad->GetGamePad()->m_state.Gamepad.sThumbRY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		pGamePad->GetGamePad()->m_state.Gamepad.sThumbRY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		float RX = pGamePad->GetGamePad()->m_state.Gamepad.sThumbRX;
		float RY = pGamePad->GetGamePad()->m_state.Gamepad.sThumbRY;

		float magnitude = sqrtf(RX*RX + RY*RY);

		float normalizedRX = RX / magnitude;
		float normalizedRY = RY / magnitude;

		// 角度を求める(XYを逆にして引数に入れると↑から0度になる)
		float fAngle = (float)atan2(normalizedRX, normalizedRY);
		return fAngle;
	}

	else
	{
		return m_fAngle;
	}
}

