//-----------------------------------------------------------------------------
//ゲームパッド操作の処理
//-----------------------------------------------------------------------------
#include <Windows.h>
#include "XInput.h"
#include "player.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CXInput::CXInput()
{
	ZeroMemory(&m_GamePad.m_state, sizeof(XINPUT_STATE));
	ZeroMemory(&m_GamePad.m_stateLast, sizeof(XINPUT_STATE));
	ZeroMemory(&m_GamePad.m_vibration, sizeof(XINPUT_VIBRATION));
}

//=============================================================================
// デストラクタ
//=============================================================================
CXInput::~CXInput()
{
	// Xinputを終了
	XInputEnable(false); // BOOL enable
}

//-----------------------------------------------------------------------------
//更新処理
//-----------------------------------------------------------------------------
void CXInput::UpdateGamepad(void)
{
	XINPUT_STATE state;

	DWORD dwResult = XInputGetState(0, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		m_GamePad.m_stateLast = m_GamePad.m_state;
		m_GamePad.m_state = state;
	}
}

bool CXInput::GetButtonTrigger(int nButton)
{
	return (m_GamePad.m_stateLast.Gamepad.wButtons & nButton) == false && (m_GamePad.m_state.Gamepad.wButtons & nButton) ? true : false;
}

bool CXInput::GetGamepadPress(int nButton)
{
	return (m_GamePad.m_state.Gamepad.wButtons & nButton);
}

CXInput::GAMEPAD *CXInput::GetGamePad(void)
{
	return &m_GamePad;
}