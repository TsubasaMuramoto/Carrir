//=================================================
// 当たり判定の作成
// Author:村元 翼
//=================================================

//=================================================
// インクルードファイル ＆ 前方宣言
//=================================================
#include "main.h"
#include "scene2D.h"
#include "scene.h"

//=================================================
// マクロ定義
//=================================================
#define _OX_EPSILON_ 0.000001f	// 誤差

//=================================================
// クラスの作成
//=================================================
class CCollision
{
public:
	CCollision();
	~CCollision();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	bool SetCollision(CScene *pHit1,CScene *pHit2);
	bool CircleCollision(CScene *pCircle, CScene *pSquare);

private:

};

// 当たり判定に必要なもの