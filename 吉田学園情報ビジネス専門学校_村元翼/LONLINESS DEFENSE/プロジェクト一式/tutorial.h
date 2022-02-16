//--------------------------------------
// チュートリアルの処理
//--------------------------------------
#ifndef _TUTORIAL_H
#define _TUTORIAL_H
#include "main.h"
#include "scene.h"

//--------------------------------------
// マクロ定義
//--------------------------------------
#define MAX_TUTORIAL_POLYGON (5)

//--------------------------------------
//前方宣言
//--------------------------------------
class CBg;
class CScene2D;

//----------------------------------------
// チュートリアルクラスの作成
//----------------------------------------
class CTutorial
{
public:

	CTutorial();
	~CTutorial();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void NextMode(bool bNextMode) { m_bNextMode = bNextMode; }

private:
	CScene2D			*m_pTutorial[2];	// ページ数のチュートリアルポリゴン		
	bool				m_bNextMode;		// 次のモードに行くための
};


#endif //_TITLE_H