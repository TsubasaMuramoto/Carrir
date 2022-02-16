//--------------------------------------
//タイトルの処理
//--------------------------------------
#ifndef _TITLE_H
#define _TITLE_H
#include "main.h"
#include "scene.h"

//--------------------------------------
//マクロ定義
//--------------------------------------
#define MAX_TITLE_POLYGON (2)
#define BLINK_INTERVAL (60)

//--------------------------------------
//前方宣言
//--------------------------------------
class CBg;
class CScene2D;

//----------------------------------------
// タイトルクラスの作成
//----------------------------------------
class CTitle
{
public:
	typedef enum
	{
		GAME_START = 0,
		OPERATION,
		MAX,
	}TYPE;

	CTitle();
	~CTitle();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void NextMode(bool bNextMode) { m_bNextMode = bNextMode; }

private:
	CScene2D			*m_pTitle[MAX_TITLE_POLYGON];	// シーン2Dクラス
	int					m_nSelectType;					// 選択したタイプ
	int					m_nFrame;						// フレーム数
	int					m_nMultiFrame;					// フレーム数に掛ける数
	bool				m_bNextMode;					// 次のモードに行くための
};


#endif //_TITLE_H