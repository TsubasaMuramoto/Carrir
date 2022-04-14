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
class CRanking;

//--------------------------------------
// リザルトクラスの生成
//--------------------------------------
class CResult
{
public:

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
	CRanking			*m_pRanking;					// ランキングのポインタ
	bool				m_bNextMode;					// 次のモードに行くためのbool変数

};


#endif //_RESULT_H