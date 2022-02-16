//--------------------------------------
// リザルトの処理
//--------------------------------------
#ifndef _RESULT_H
#define _RESULT_H
#include "main.h"
#include "scene.h"

//--------------------------------------
// マクロ定義
//--------------------------------------
#define MAX_RESULT				(4)
#define RESULT_RANKING_POSY		(60.0f)			// ランキングのY座標

//--------------------------------------
// 前方宣言
//--------------------------------------
class CBg;
class CPolygon;
class CRanking;

//--------------------------------------
// リザルトクラスの生成
//--------------------------------------
class CResult
{
public:

	//--------------------------------------
	// 選択肢構造体
	//--------------------------------------
	typedef enum
	{
		GAME_RETRY = 0,
		TITLE,
		MAX,
	}TYPE;

	//--------------------------------------
	// メソッド
	//--------------------------------------
	CResult();
	~CResult();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void NextMode(bool bNextMode) { m_bNextMode = bNextMode; }

private:
	CPolygon			*pPolygon[MAX_RESULT];			// ポリゴンクラス(選択肢を表示)
	CPolygon			*m_Cursol;						// ポリゴンクラス(カーソルを表示)
	CRanking			*m_pRanking;					// ランキングのポインタ

	bool				m_bNextMode;					// 次のモードに行くためのbool変数
	int					m_nSelectType;					// 現在の選択

};


#endif //_RESULT_H