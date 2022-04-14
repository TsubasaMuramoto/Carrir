//----------------------------------
//オブジェクトの処理
//----------------------------------
#ifndef _SCENE_H_
#define _SCENE_H_
#include "main.h"

//----------------------------------
// クラス宣言
//----------------------------------
class CScene
{
public:

	//----------------------------------------------------
	// オブジェクトのタイプ構造体
	//----------------------------------------------------
	typedef enum
	{
		OBJTYPE_NONE = 0,			// なし
		OBJTYPE_BG,					// 背景
		OBJTYPE_TARGET,				// ターゲット
		OBJTYPE_ENEMY,				// 敵
		OBJTYPE_BULLET,				// 弾
		OBJTYPE_FIELD,				// 床
		OBJTYPE_EFFECT,				// エフェクト
		OBJTYPE_PLAYER,				// プレイヤー
		OBJTYPE_POLYGON,			// ポリゴン
		OBJTYPE_NUMBER,				// ナンバー
		OBJTYPE_UI,					// UI
		OBJTYPE_PAUSE,				// ポーズ
		OBJTYPE_FADE,				// フェード
		OBJTYPE_MAX
	}OBJTYPE;

	CScene();
	explicit CScene(OBJTYPE nPriority);
	virtual~CScene();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	//-----------------------------
	// Getter & Setter
	//-----------------------------
	void SetObjType(OBJTYPE objType)	{ m_ObjType = objType; }
	void SetPos(D3DXVECTOR3 pos)		{ m_pos = pos; }
	void SetScale(D3DXVECTOR3 Scale)	{ m_Scale = Scale; }
	void SetMove(D3DXVECTOR3 move)		{ m_move = move; }
	void SetTex(D3DXVECTOR2 tex)		{ m_Tex = tex; }
	void LifeSub(int nPow);

	int GetLife(void)					{ return m_nLife; }
	CScene::OBJTYPE GetObjType(void)	{ return m_ObjType; }
	D3DXVECTOR3 GetPos(void)			{ return m_pos; }
	D3DXVECTOR3 GetScale(void)			{ return m_Scale; }
	D3DXVECTOR3 GetMove(void)			{ return m_move; }
	D3DXVECTOR2 GetTex(void)			{ return m_Tex; }
	bool GetDamage(void)				{ return m_bDamage; }
	bool GetDeath(void)					{ return m_bDeath; }

	static CScene *GetScene(const int nPriority)	{ return m_pTop[nPriority]; }
	static CScene *GetSceneNext(CScene *pTop)		{ return pTop->m_pNext; }

	static void ReleaseAll(void);	// 全てのインスタンスの破棄処理
	static void UpdateAll(void);	// 全てのオブジェの更新	
	static void DrawAll(void);		// 全てのオブジェの描画
	
private:
	D3DXVECTOR3				m_pos,m_oldpos;					// 基準の位置
	D3DXVECTOR3				m_move;							// 移動量
	D3DXVECTOR3				m_Scale;						// 大きさ
	D3DXVECTOR2				m_Tex;							// テクスチャの大きさ
	OBJTYPE					m_ObjType;						// オブジェクトタイプの種類
	static int				m_nNumAll[OBJTYPE_MAX];			// タイプごとのオブジェ数
	int						m_nID;							// 格納先の番号
	int						m_nLife;						// ライフ
	int						m_nPriority;					// 優先順位
	bool					m_bDamage;						// ダメージ判定

	static CScene			*m_pTop[OBJTYPE_MAX];			// 先頭のオブジェクトのポインタ
	static CScene			*m_pCur[OBJTYPE_MAX];			// 現在（一番後ろ）のオブジェクトのポインタ
	CScene					*m_pPrev;						// 前のオブジェクトへのポインタ
	CScene					*m_pNext;						// 次のオブジェクトへのポインタ
	bool					m_bDeath;

protected:
	void Release(void);//オブジェクト単体のインスタンス破棄

};
#endif // !_SCENE_H_
