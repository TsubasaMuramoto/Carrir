//--------------------------------------
//マネージャーの処理
//--------------------------------------
#ifndef _MANAGER_H
#define _MANAGER_H
#include "main.h"

//--------------------------------------
// 前方宣言
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
// クラス定義
//--------------------------------------
class CManager
{
public:

	//---------------------------------------------------
	// モードの状態構造体
	//---------------------------------------------------
	typedef enum
	{
		MODE_TITLE = 0,			// タイトル画面
		MODE_TUTORIAL,			// チュートリアル画面
		MODE_GAME,				// ゲーム画面
		MODE_RESULT,			// リザルト画面
		MODE_MAX
	}MODE;


	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//----------------------------
	// Getter & Setter
	//----------------------------
	static CManager			*GetInstance(void);									// インスタンス取得
	static CRenderer		*GetRenderer(void)		{ return m_pRenderer; }		// レンダラーの取得
	static CTexture			*GetTexture(void)		{ return m_pTexture; }		// テクスチャの取得
	static CInputkeyboard	*GetKeyboard()			{ return m_pKeyboard; }		// キーボードの取得
	static CMouse			*GetMouse()				{ return m_pMouse; }		// マウスの取得
	static CGame			*GetGame(void)			{ return m_pGame; }			// ゲームの取得
	static CPause			*GetPause(void)			{ return m_pPause; }		// ポーズの取得
	static CXInput			*GetXInput(void)		{ return m_pXInput; }		// Xinputの取得
	static CPlayData		*GetPlayData(void)		{ return m_pPlayData; }		// プレイデータ取得
	static CSound			*GetSound(void)			{ return m_pSound; }		// サウンド取得
	static MODE				GetMode(void)			{ return m_Mode; }			// モードの取得
	static bool				GetStop(void)			{ return m_bPause; }		// ポーズ判定の取得

	static void SetMode(MODE mode);																	// モードの設定
	static void SetPause(bool bPause, bool bStop = false) { m_bPause = bPause; m_bStop = bStop;}	// ポーズの設定

private:
	//---------------------------------------------------
	// コンストラクタ・デストラクタ
	//---------------------------------------------------
	CManager();
	~CManager();

	//---------------------------------------------------
	// メンバ変数
	//---------------------------------------------------
	static CManager			*s_pManager;		// マネージャーのクラス
	static CTitle			*m_pTitle;			// タイトルクラス
	static CGame			*m_pGame;			// ゲームクラス
	static CTutorial		*m_pTutorial;		// チュートリアルクラス
	static CResult			*m_pResult;			// リザルトクラス
	static CRenderer		*m_pRenderer;		// レンダラークラス
	static CTexture			*m_pTexture;		// テクスチャクラス
	static CInputkeyboard	*m_pKeyboard;		// キーボードクラス
	static CXInput			*m_pXInput;			// Xinputのクラス
	static CFade			*m_pFade;			// フェードクラス
	static MODE				m_Mode;				// 現在のモード
	static CPause			*m_pPause;			// ポーズクラス
	static CMouse			*m_pMouse;			// マウスクラス
	static CPlayData		*m_pPlayData;		// プレイデータクラス
	static CSound			*m_pSound;			// サウンドクラス

	static bool				m_bGamepadSwitch;	// ゲームパッド入力のオンオフ
	static bool				m_bStop;			// ストップするか
	static bool				m_bPause;			// ポーズにするか
};
#endif //_MANAGER_H