//--------------------------------------
// PAUSEの処理
// Author: 
//--------------------------------------
#ifndef _PAUSE_H
#define _PAUSE_H
#include "main.h"
#include "scene.h"
#include "texture.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define MAX_PAUSE (3)
#define PAUSE_INERVAL (100.0f)
#define SELECT_HEIGHT (300.0f)
#define SELECT_SIZE (D3DXVECTOR3(350.0f,60.0f,0.0f))

//-------------------------------------------
// 前方宣言
//-------------------------------------------
class CPolygon;
class CScene2D;
class CBg;

//---------------------------------------------
// ポーズのクラス
//---------------------------------------------
class CPause : public CScene
{
public:
	//-----------------------------------------
	// ポーズフェードの状態構造体
	//-----------------------------------------
	typedef enum
	{
		FADE_IN = 0,
		FADE_OUT,
	}PAUSE_FADE;

	CPause(OBJTYPE nPriority = OBJTYPE_PAUSE);
	~CPause();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPause *Create(D3DXVECTOR3 pos);			// インスタンス生成処理

private:
	//void FadeInOut(int nFade);						// ポーズのフェードに使う関数？
	//void SetPAUSE(int nType);						// PAUSEに使うポリゴンの生成？
	D3DXVECTOR3		m_pos;							// 位置
	D3DXVECTOR3		m_Speed;						// 速度
	float			m_fAlpha;						// ポーズ背景の透明度
	int				m_nPauseType;					// ポーズ選択
	bool			m_bUninit;						// pauseを終了させるか
	bool			m_bNextMode;					// 次のモードにいくか
	CScene2D		*m_pPolygon[MAX_PAUSE];			// ポーズ選択のポリゴン
	CScene2D		*m_pCursor;						// 選択カーソルのポリゴン
	CScene2D		*m_pTutorialUI;					// 操作説明UI
	static CBg		*m_pBg;							// ポーズ背景

};


#endif //_PAUSE_H