//--------------------------
// �����_���[�̍쐬
// Author:������
//----------------------------
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "main.h"

//--------------------------
// �����_�����O�N���X
//----------------------------
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//--------------------------
	// Getter
	//--------------------------
	LPDIRECT3DDEVICE9 GetDevice(void);
	LPD3DXFONT GetFont(void) { return m_pFont; }
	static HWND GethWnd(void);

private:
#ifdef _DEBUG
	void DrawFPS(void);	// FPS�̕\���֐�
	void DrawTXT(void);	// �f�o�b�O�����̕\���֐�
#endif

	LPDIRECT3D9				m_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;	// Device�I�u�W�F�N�g(�`��ɕK�v)
	LPD3DXFONT				m_pFont = NULL;			// �t�H���g�ւ̃|�C���^
	static HWND				m_hWnd;					// �E�B���h�E�n���h��
};
#endif
