//=============================================================================
//
// �v���C���[
// Author : ������
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
// �ÓI�����o�ϐ��̏�����
//=============================================================================
const D3DXVECTOR2 CPlayer::m_ScrollRange = D3DXVECTOR2(200.0f, 100.0f);
const D3DXVECTOR2 CPlayer::m_ScrollRange2 = D3DXVECTOR2(1080.0f, 620.0f);

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(OBJTYPE nPriority) : CScene2D(nPriority)
{
	m_pos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_rot				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]
	m_scale				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �傫��
	m_velocity			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���ۂ̑��x
	m_Direction			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	m_Speed				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���x
	m_fMaxSpeed			= MAX_SPEED;						// �ő呬�x
	m_fAngle			= 0.0f;								// �p�x
	m_fShootInterval	= 0.0f;								// �ˌ��Ԋu
	m_RotateVertex[0]	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RotateVertex[1]	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RotateVertex[2]	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RotateVertex[3]	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//------------------------------------------------------------
// ���_���W�̐ݒ�
//------------------------------------------------------------
void CPlayer::SetPos(D3DXVECTOR3 pos)
{
	CScene::SetPos(pos);

	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �o�b�t�@�̐���
	pVtx[0].pos = D3DXVECTOR3(pos.x - m_scale.x, pos.y - m_scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + m_scale.x, pos.y - m_scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - m_scale.x, pos.y + m_scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + m_scale.x, pos.y + m_scale.y, 0.0f);

	m_pVtxBuff->Unlock();
}

//=============================================================================
// ������
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
// �I��
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CPlayer::Update(void)
{
	CXInput *pGamePad = CManager::GetXInput();
	CMouse *pMouse = CManager::GetMouse();

	CScene2D::Update();
	CScene::SetMove(m_Speed);
	CScene2D::SetPos(m_pos,m_scale,&m_RotateVertex[0]);
	Move();		// �v���C���[�̈ړ�

	//==========================================================================================================
	// �e�̔���
	//==========================================================================================================
	if (m_fShootInterval > 0.0f)
	{
		m_fShootInterval -= 0.1f;		// ���ɒe���łĂ�܂ł̃C���^�[�o�������炷
		pGamePad->SetVibration(0,0);	// �U����~
	}

	else
	{
		// �}�E�X�N���b�Nor�Q�[���p�b�hR2
		if (pMouse->GetPress(pMouse->MOUSE_LEFT) || pGamePad->GetGamePad()->m_state.Gamepad.bRightTrigger >= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			CBullet::Create(m_pos, BULLET_SIZE, m_fAngle);						// �e�𐶐�
			m_fShootInterval = SHOOT_INTERVAL;									// �e�̃C���^�[�o����ݒ肷��
			pGamePad->SetVibration(VIBRATION_POWER_MAX, VIBRATION_POWER_MAX);	// �R���g���[���U��
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void CPlayer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̃|�C���^

	// �A���t�@�u�����h
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL);

	CScene2D::Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
}

//=============================================================================
// �v���C���[�̐���
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, CTexture::Type texture)
{
	// �C���X�^���X����
	CPlayer *pPlayer = nullptr;

	if (pPlayer == nullptr)
	{
		pPlayer = new CPlayer(OBJTYPE_PLAYER);

		if (pPlayer != nullptr)
		{
			// �v���C���[���̎擾
			pPlayer->m_pos = pos;
			pPlayer->m_scale = scale;
			pPlayer->m_Tex = texture;

			// ����������
			pPlayer->Init();
		}
	}
	return pPlayer;
}

//=============================================================================
// �v���C���[�̈ړ�
//=============================================================================
void CPlayer::Move(void)
{
	// �Q�[���p�b�h���ڑ�����Ă��邩
	CXInput *pXInput = CManager::GetXInput();
	XINPUT_STATE state;
	DWORD IsConnected = XInputGetState(0, &state);
	if (IsConnected == ERROR_SUCCESS)
	{
		m_fAngle = RotateGamePad(pXInput);			// �Q�[���p�b�h���͂ł̊p�x�����߂鏈��
	}
	else
	{
		m_fAngle = FeaturedMouse(m_pos, m_Point);	// �}�E�X�J�[�\���Ƀv���C���[����������
	}

	//=============================================================================
	// �v���C���[�̈ړ������߂�
	//=============================================================================
	// �O�ɐi��
	if (InputDirection(DIRECTION_UP))
	{
		m_Direction.y = 1.0f;
		m_Speed.y -= 0.2f;
	}

	// ���ɐi��
	else if (InputDirection(DIRECTION_DOWN))
	{
		m_Direction.y = 1.0f;
		m_Speed.y += 0.2f;
	}

	// �O�㉟���Ă��Ȃ����
	else if (InputDirection(DIRECTION_NO_UP) && InputDirection(DIRECTION_NO_DOWN))
	{
		m_Direction.y = 0.0f;
	}

	// �E�ɐi��
	if (InputDirection(DIRECTION_RIGHT))
	{
		m_Direction.x = 1.0f;
		m_Speed.x += 0.2f;
	}

	// ���ɐi��
	else if (InputDirection(DIRECTION_LEFT))
	{
		m_Direction.x = -1.0f;
		m_Speed.x -= 0.2f;
	}

	// ���E�����Ă��Ȃ����
	else if (InputDirection(DIRECTION_NO_LEFT) && InputDirection(DIRECTION_NO_RIGHT))
	{
		m_Direction.x = 0.0f;
	}

	//==========================================================================================================
	// �ړ�����(���W�X�V)
	//==========================================================================================================
	m_pos.x += m_Speed.x;
	m_pos.y += m_Speed.y;

	//==========================================================================================================
	// �G�t�F�N�g�����ƃ��[�^�[�U��
	//==========================================================================================================
	if (InputDirection(DIRECTION_UP) || InputDirection(DIRECTION_DOWN) ||
		InputDirection(DIRECTION_LEFT) || InputDirection(DIRECTION_RIGHT))
	{
		// �U��������
		pXInput->SetVibration(VIBRATION_POWER_RIGHT, VIBRATION_POWER_LEFT);

		// �G�t�F�N�g����
		CEffect::Create(m_pos, m_Speed, m_scale, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.5f,0.01f, m_fAngle,CEffect::EFFECT_PLAYER);
	}

	else
	{
		// ���[�^�[�̗͂�0�ɂ���(�U�����~)
		pXInput->SetVibration(0, 0);
	}

	//==========================================================================================================
	// �ړ��Ɏg���֐�
	//==========================================================================================================
	GetCursorPos(&m_Point);									// �}�E�X�J�[�\�����W�̎擾(�X�N���[�����W)
	ScreenToClient(CRenderer::GethWnd(), &m_Point);			// �}�E�X�̃X�N���[�����W���N���C�A���g���W�ɕϊ�
	Acceleration(m_velocity, m_Speed, m_fMaxSpeed);			// ����
	Rotate(m_pos, m_scale, m_fAngle);						// ��]
	MovingLimit(m_pos, m_scale, m_Speed);					// �ړ����E

}

//=============================================================================
// �v���C���[�̊���
//=============================================================================
void CPlayer::Acceleration(D3DXVECTOR3& velo, D3DXVECTOR3& speed,const float &Maxspeed)
{
	m_velocity = velo;
	m_Speed = speed;
	m_fMaxSpeed = Maxspeed;

	//------------------------------------------------
	// ���E���͂��Ă��Ȃ����
	//------------------------------------------------
	if (m_Direction.x == 0.0f)
	{
		// 0�ɖ߂葱���鏈��
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
	// �㉺���͂��Ă��Ȃ����
	//------------------------------------------------
	if (m_Direction.y == 0.0f)
	{
		// 0�ɖ߂葱���鏈��
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
	// �ő�X�s�[�h
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

	// �E�ړ��́{�����A���ړ��́|�����A�����Ȃ�������0
	m_velocity = m_Speed;
}

//=============================================================================
// �����̉�]���s���֐�
//=============================================================================
void CPlayer::Rotate(D3DXVECTOR3 pos, D3DXVECTOR3 scale, float Angle)
{
	D3DXVECTOR3 vertex[4];

	// 4���_�̐ݒ�
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
// �ړ����E�ɓ��B�������̊֐�
//=============================================================================
void CPlayer::MovingLimit(D3DXVECTOR3 &pos, D3DXVECTOR3 &scale, D3DXVECTOR3 &speed)
{
	// �X�N���[�����n�߂�͈�(��)
	if (pos.x + (scale.x / 2) >= m_ScrollRange2.x || pos.x - (scale.x / 2) <= m_ScrollRange.x)
	{
		// �E�X�N���[��������͈�
		if (pos.x + (scale.x / 2) >= m_ScrollRange2.x)
		{
			if (CGame::GetBg()->GetPos().x >= CBg::GetRangeMax().x)		// �w�i����ԉE�ɍs�����Ƃ�
			{
				// �E�B���h�E�̉E�[�܂Ńv���C���[���s��
				if (pos.x + (scale.x / 2) > SCREEN_WIDTH)
				{
					pos.x = SCREEN_WIDTH - (scale.x / 2);				// �v���C���[�ʒu���E�B���h�E�͈͓��ɖ߂�
					speed.x = 0.0f;
				}

				CGame::SetScroll("StopX", speed);
			}

			else
			{
				pos.x = m_ScrollRange2.x - (scale.x / 2);				// �v���C���[�ʒu���X�N���[���͈͓��ɖ߂�
				CGame::SetScroll("X", speed);							// �X�N���[����ݒ肷��
			}
		}

		// ���X�N���[��������͈�
		if (pos.x - (scale.x / 2) <= m_ScrollRange.x)
		{
			if (CGame::GetBg()->GetPos().x <= CBg::GetRangeMin().x)	// ��
			{
				// �E�B���h�E�̍��[�܂Ńv���C���[���s��
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
		CGame::SetScroll("StopX", speed);						// ���X�N���[�����X�g�b�v
	}

	// �X�N���[�����n�߂�͈�(�c)
	if (pos.y + (scale.y / 2) >= m_ScrollRange2.y || pos.y - (scale.y / 2) <= m_ScrollRange.y)
	{
		// ���X�N���[���͈͂܂ōs������
		if (pos.y + (scale.y / 2) >= m_ScrollRange2.y)
		{
			if (CGame::GetBg()->GetPos().y >= CBg::CBg::GetRangeMax().y)	// �w�i�����E�܂ōs�����Ƃ�
			{
				// �E�B���h�E�̉��[�܂Ńv���C���[���s��
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

		// ��X�N���[���͈͂܂ōs������
		if (pos.y - (scale.y / 2) <= m_ScrollRange.y)
		{
			if (CGame::GetBg()->GetPos().y <= CBg::CBg::GetRangeMin().y)	// ��
			{
				// �E�B���h�E�̏�[�܂Ńv���C���[���s��
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
		CGame::SetScroll("StopY", speed);			// �c�X�N���[�����X�g�b�v
	}

}

//=============================================================================
// �}�E�X�J�[�\���̈ʒu�Ɋp�x�������֐�
//=============================================================================
float CPlayer::FeaturedMouse(D3DXVECTOR3 pos, POINT mousePoint)
{
	// �I�u�W�F�N�g�̈ʒu�ƃ}�E�X�J�[�\���̈ʒu�̍��������߂�
	const float fLengthX = (pos.x - mousePoint.x);
	const float fLengthY = (pos.y - mousePoint.y);

	// �p�x�����߂�(XY���t�ɂ��Ĉ����ɓ����Ɓ�����0�x�ɂȂ�)
	const float fAngle = -atan2f(fLengthX, fLengthY);

	return fAngle;
}

//=============================================================================
// �Q�[���p�b�h�ŉ�]���s���֐�
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

		// �p�x�����߂�(XY���t�ɂ��Ĉ����ɓ����Ɓ�����0�x�ɂȂ�)
		const float fAngle = atan2f(normalizedRX, normalizedRY);
		return fAngle;
	}

	else
	{
		return m_fAngle;
	}
}

//=============================================================================
// ���͕���
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

