//-----------------------------------------------------
//フェードの処理
//-----------------------------------------------------
#ifndef _FADE_H_
#define _FADE_H_
#include "texture.h"
#include "manager.h"
#include "scene2D.h"

//-----------------------------------------------------
// 前方宣言
//-----------------------------------------------------
class CBg;

//-----------------------------------------------------
// クラス宣言
//-----------------------------------------------------
class CFade : public CScene
{
public:
	//----------------------------------
	// フェードの状態構造体
	//----------------------------------
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX,
	} FADE;

	CFade(OBJTYPE nPriority = OBJTYPE_FADE);
	~CFade();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetFade(CManager::MODE modeNext);						// フェードの設定
	FADE GetFade(void);													// フェードの取得
	static CFade *Create(CTexture::Type type,CManager::MODE modeNext);	// インスタンス生成処理

private:
	CTexture::Type				m_Type;			// テクスチャタイプ
	static CBg					*m_pBg;			// 背景クラス
	static FADE					m_fade;			// フェードの状態
	static CManager::MODE		m_modeNext;		// 次の画面（モード）
	static float				m_colorAlpha;	// フェードの色

};
#endif // !_FADE_H_

