//--------------------------
// レンダラーの作成
// Author:村元翼
//----------------------------
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "main.h"

//--------------------------
// レンダリングクラス
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
	void DrawFPS(void);	// FPSの表示関数
	void DrawTXT(void);	// デバッグ文字の表示関数
#endif

	LPDIRECT3D9				m_pD3D = NULL;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;	// Deviceオブジェクト(描画に必要)
	LPD3DXFONT				m_pFont = NULL;			// フォントへのポインタ
	static HWND				m_hWnd;					// ウィンドウハンドル
};
#endif
