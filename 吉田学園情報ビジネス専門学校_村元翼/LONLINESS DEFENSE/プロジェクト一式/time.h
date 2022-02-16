//---------------------------------------------------------------
// タイムの作成
//---------------------------------------------------------------
#ifndef _TIME_H_
#define _TIME_H_
#include "scene.h"
#include "texture.h"

//---------------------------------------------------------------
// マクロ定義
//---------------------------------------------------------------
#define MAX_TIME (3)	// 描画するポリゴン枚数
#define TIME (60)		// 制限時間

//---------------------------------------------------------------
// 前方宣言
//---------------------------------------------------------------
class CNumber;

//---------------------------------------------------------------
// タイムクラス(シーンの派生)
//---------------------------------------------------------------
class CTime : public CScene
{
public:
	CTime(OBJTYPE nPriority = OBJTYPE_NUMBER);
	~CTime();

	static CTime *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);// 生成
	HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 size);			// 初期化
	HRESULT Init();											// 初期化
	void Uninit(void);										// 終了
	void Update(void);										// 更新
	void Draw(void);										// 描画
	void SetTime(void);										// 描画されているテクスチャの設定

private:
	int		m_nTime;									// 現在の時間
	int		m_nFrame = 0;								// フレーム数
	int		m_nAll;										// タイムポリゴン数
	bool	m_bNextMode;								// 次のモードに行くための変数
	CNumber *m_apNumber[MAX_TIME];						// タイムに使うポリゴン
};

#endif // !_TIME_H_*/


