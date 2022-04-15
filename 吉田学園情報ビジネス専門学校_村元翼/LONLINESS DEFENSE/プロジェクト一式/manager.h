//--------------------------------------
//�}�l�[�W���[�̏���
//--------------------------------------
#ifndef _MANAGER_H
#define _MANAGER_H
#include "main.h"

//--------------------------------------
// �O���錾
//--------------------------------------
class CRenderer;
class CTexture;
class CPolygon;
class CInputkeyboard;
class CTitle;
class CTutorial;
class CGame;
class CResult;
class CFade;
class CPause;
class CMouse;
class CXInput;
class CPlayData;
class CSound;
//--------------------------------------
// �N���X��`
//--------------------------------------
class CManager
{
public:

	//---------------------------------------------------
	// ���[�h�̏�ԍ\����
	//---------------------------------------------------
	typedef enum
	{
		MODE_TITLE = 0,			// �^�C�g�����
		MODE_TUTORIAL,			// �`���[�g���A�����
		MODE_GAME,				// �Q�[�����
		MODE_RESULT,			// ���U���g���
		MODE_MAX
	}MODE;


	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//----------------------------
	// Getter & Setter
	//----------------------------
	static CManager			*GetInstance(void);									// �C���X�^���X�擾
	static CRenderer		*GetRenderer(void)		{ return m_pRenderer; }		// �����_���[�̎擾
	static CTexture			*GetTexture(void)		{ return m_pTexture; }		// �e�N�X�`���̎擾
	static CInputkeyboard	*GetKeyboard()			{ return m_pKeyboard; }		// �L�[�{�[�h�̎擾
	static CMouse			*GetMouse()				{ return m_pMouse; }		// �}�E�X�̎擾
	static CGame			*GetGame(void)			{ return m_pGame; }			// �Q�[���̎擾
	static CPause			*GetPause(void)			{ return m_pPause; }		// �|�[�Y�̎擾
	static CXInput			*GetXInput(void)		{ return m_pXInput; }		// Xinput�̎擾
	static CPlayData		*GetPlayData(void)		{ return m_pPlayData; }		// �v���C�f�[�^�擾
	static CSound			*GetSound(void)			{ return m_pSound; }		// �T�E���h�擾
	static MODE				GetMode(void)			{ return m_Mode; }			// ���[�h�̎擾
	static bool				GetStop(void)			{ return m_bPause; }		// �|�[�Y����̎擾

	static void SetMode(MODE mode);																	// ���[�h�̐ݒ�
	static void SetPause(bool bPause, bool bStop = false) { m_bPause = bPause; m_bStop = bStop;}	// �|�[�Y�̐ݒ�

private:
	//---------------------------------------------------
	// �R���X�g���N�^�E�f�X�g���N�^
	//---------------------------------------------------
	CManager();
	~CManager();

	//---------------------------------------------------
	// �����o�ϐ�
	//---------------------------------------------------
	static CManager			*s_pManager;		// �}�l�[�W���[�̃N���X
	static CTitle			*m_pTitle;			// �^�C�g���N���X
	static CGame			*m_pGame;			// �Q�[���N���X
	static CTutorial		*m_pTutorial;		// �`���[�g���A���N���X
	static CResult			*m_pResult;			// ���U���g�N���X
	static CRenderer		*m_pRenderer;		// �����_���[�N���X
	static CTexture			*m_pTexture;		// �e�N�X�`���N���X
	static CInputkeyboard	*m_pKeyboard;		// �L�[�{�[�h�N���X
	static CXInput			*m_pXInput;			// Xinput�̃N���X
	static CFade			*m_pFade;			// �t�F�[�h�N���X
	static MODE				m_Mode;				// ���݂̃��[�h
	static CPause			*m_pPause;			// �|�[�Y�N���X
	static CMouse			*m_pMouse;			// �}�E�X�N���X
	static CPlayData		*m_pPlayData;		// �v���C�f�[�^�N���X
	static CSound			*m_pSound;			// �T�E���h�N���X

	static bool				m_bGamepadSwitch;	// �Q�[���p�b�h���͂̃I���I�t
	static bool				m_bStop;			// �X�g�b�v���邩
	static bool				m_bPause;			// �|�[�Y�ɂ��邩
};
#endif //_MANAGER_H