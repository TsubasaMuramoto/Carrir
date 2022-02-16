//--------------------------------------------------------------
// スコアの作成
// Author
//--------------------------------------------------------------
#ifndef _SCORE_H_
#define _SCORE_H_

//--------------------------------------------------------------
// インクルードファイル ＆ 前方宣言
//--------------------------------------------------------------
#include "scene.h"
class CNumber;

//--------------------------------------------------------------
// マクロ定義
//--------------------------------------------------------------
#define MAX_SCORE (6)			// 最大描画枚数

//---------------------------------------------------------------
// スコアクラス(シーンの派生)
//---------------------------------------------------------------
class CScore : public CScene
{
public:
	CScore(OBJTYPE nPriority = OBJTYPE_NUMBER);
	~CScore();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 fsize);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScore	*Create(D3DXVECTOR3 pos, D3DXVECTOR3 fsize);			// スコアの生成
	void		AddScore(int AddScore)	{ m_nScore += AddScore; };		// スコアの加算
	void			SetScore(void);											// スコアの描画設定
	void			SetScore(int nScore);
	void			SetScorePos(D3DXVECTOR3 pos);
	CNumber			*GetNumber(int nNumber) { return m_apNumber[nNumber]; }
	int				GetScore(void)			{ return m_nScore; }

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	CNumber *m_apNumber[MAX_SCORE];									// スコアのポリゴン
	int m_nAddScore;												// スコア加算用変数
	int m_nAll;														// スコアポリゴン数
	int m_nScore;											// 現在のスコア
};
#endif
