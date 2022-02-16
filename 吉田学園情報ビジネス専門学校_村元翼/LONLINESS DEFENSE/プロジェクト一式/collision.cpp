//=================================================
// 当たり判定の作成
// Author:村元 翼
//=================================================
#include "collision.h"

//=================================================
// コンストラクタ
//=================================================
CCollision::CCollision()
{

}

//=================================================
// デストラクタ
//=================================================
CCollision::~CCollision()
{

}

//=================================================
// 初期化
//=================================================
HRESULT CCollision::Init()
{
	return S_OK;
}

//=================================================
// 終了
//=================================================
void CCollision::Uninit()
{
	
}

//=================================================
// 更新
//=================================================
void CCollision::Update()
{

}

//=================================================
// 通常当たり判定
//=================================================
bool CCollision::SetCollision(CScene *pHit1, CScene *pHit2)
{
	D3DXVECTOR3 pos1;		// 物体Aの位置
	D3DXVECTOR3 pos2;		// 物体Bの位置
	D3DXVECTOR3 size1;		// 物体Aの大きさ
	D3DXVECTOR3 size2;		// 物体Bの大きさ

	pos1 = pHit1->GetPos();
	pos2 = pHit2->GetPos();
	size1 = pHit1->GetScale();
	size2 = pHit2->GetScale();

	D3DXVECTOR3 vec = pos2 - pos1;		// 二つの位置の差分を求める

	float fLength = sqrtf((vec.y * vec.y));
	float fLength2 = sqrtf((vec.x * vec.x));

	// 当たり判定の処理
	if (fLength <= size1.y &&
		fLength2 <= size1.x)
	{
		//当たったという判定を返す
 		return true;
	}

	// 当たっていなかったらfalse
	return false;

}

//=================================================
// 円と四角形の当たり判定
//=================================================
bool CCollision::CircleCollision(CScene *pCircle, CScene *pSquare)
{
	D3DXVECTOR3 CirclePos;		// 円の位置
	float		CircleRadius;	// 円の半径
	D3DXVECTOR3 SquarePos;		// 矩形の位置
	D3DXVECTOR3 SquareRadius;	// 矩形の大きさ

	CirclePos = pCircle->GetPos();				// 位置(中心点)取得
	SquarePos = pSquare->GetPos();				// 位置(中心点)取得
	SquareRadius = (pSquare->GetScale() / 2);	// 四角形の大きさ取得

	// x,yの大きいサイズを半径に取得する
	if (pCircle->GetScale().x >= pCircle->GetScale().y)
	{
		CircleRadius = (pCircle->GetScale().x / 2);
	}

	else
	{
		CircleRadius = (pCircle->GetScale().y / 2);
	}

	//============================================//
	//			上下左右の当たり判定			  //
	//============================================//
	// 上下
	if (CirclePos.x > (SquarePos.x - SquareRadius.x) && CirclePos.x < (SquarePos.x + SquareRadius.x) &&
		CirclePos.y >((SquarePos.y - SquareRadius.y) - CircleRadius) && CirclePos.y < ((SquarePos.y + SquareRadius.y) + CircleRadius)
		)
	{
		return true;
	}

	// 左右
	if (CirclePos.x > ((SquarePos.x - SquareRadius.x) - CircleRadius) && CirclePos.x < ((SquarePos.x + SquareRadius.x) + CircleRadius) &&
		CirclePos.y >(SquarePos.y - SquareRadius.y) && CirclePos.y < (SquarePos.y + SquareRadius.y)
		)
	{
		return true;
	}

	//======================================//
	//			角丸の当たり判定			//
	//======================================//
	// 左上
	if (pow((SquarePos.x - SquareRadius.x) - CirclePos.x, 2.0) + pow((SquarePos.y - SquareRadius.y) - CirclePos.y, 2.0) < pow(CircleRadius,2.0))
	{
		return true;
	}

	// 右上
	if (pow((SquarePos.x + SquareRadius.x) - CirclePos.x, 2.0) + pow((SquarePos.y - SquareRadius.y) - CirclePos.y, 2.0) < pow(CircleRadius, 2.0))
	{
		return true;
	}

	// 右下
	if (pow((SquarePos.x + SquareRadius.x) - CirclePos.x, 2.0) + pow((SquarePos.y + SquareRadius.y) - CirclePos.y, 2.0) < pow(CircleRadius, 2.0))
	{
		return true;
	}

	// 左下
	if (pow((SquarePos.x - SquareRadius.x) - CirclePos.x, 2.0) + pow((SquarePos.y + SquareRadius.y) - CirclePos.y, 2.0) < pow(CircleRadius, 2.0))
	{
		return true;
	}

	// 当たっていなかったら
	return false;
}
