//--------------------------------------
//タイトルの処理
//--------------------------------------
#ifndef _GAME_H
#define _GAME_H
#include "main.h"
#include "scene.h"

//---------------------------------------
// マクロ定義
//---------------------------------------
#define GAUGE_POS (D3DXVECTOR3(50.0f,50.0f,0.0f))
#define TIME_POS (D3DXVECTOR3(980.0f, 680.0f, 0.0f))
#define POP_TIMING (60)

//---------------------------------------
// 前方宣言
//---------------------------------------
class CScene2D;
class CBg;
class CPlayer;
class CTime;
class CScore;
class CEnemy;
class CPolygon;
class CTarget;
class CGauge;
class CMiniPolygon;

//------------------------------
// クラスの生成
//------------------------------
class CGame
{
public:

	//--------------------------
	// レベル管理構造体
	//--------------------------
	typedef enum
	{
		LEVEL_EASY=0,
		LEVEL_NORMAL,
		LEVEL_HARD,
		LEVEL_MAX
	}LEVEL;

	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//--------------------------
	// Getter & Setter
	//--------------------------
	static CTarget						*GetTarget(void)				{ return m_pTarget; }
	static CPlayer						*GetPlayer(void)				{ return m_pPlayer; }
	static CScore						*GetScore(void)					{ return m_pScore; }
	static std::vector<CEnemy>			*GetEnemy(void)					{ return m_vpEnemy; }
	static CBg							*GetBg(void)					{ return m_pBg; }
	static CGauge						*GetGauge(void)					{ return m_pGauge; }
	static CPolygon						*GetMiniMap(void)				{ return m_pMiniMap; }
	static CMiniPolygon					*GetMiniPolygon(void)			{ return m_pMiniPlayer; }
	static std::vector<CMiniPolygon>	*GetMiniEnemy(void)				{ return m_vpMiniEnemy; }
	static D3DXVECTOR3					GetScroll(void)					{ return m_ScrollSpeed; }
	static D3DXVECTOR3					GetScrollPos(void)				{ return m_ScrollPos; }
	static int							GetTimer(void)					{ return m_nSpawnTimer; }
	static void							SetScroll(D3DXVECTOR3 scroll)	{ m_ScrollSpeed = scroll; }
	static void							SetScroll(const char* Direction,D3DXVECTOR3 speed);

private:
	static CScene2D						*m_pGaugeFrame;
	static CScore						*m_pScore;
	static CBg							*m_pBg;
	static CPlayer						*m_pPlayer;
	static CTime						*m_pTime;
	static CPolygon						*m_pMiniMap;
	static std::vector<CEnemy>			*m_vpEnemy;
	static CTarget						*m_pTarget;
	static CGauge						*m_pGauge;
	static CMiniPolygon					*m_pMiniPlayer;
	static std::vector<CMiniPolygon>	*m_vpMiniEnemy;

	static D3DXVECTOR3	m_ScrollSpeed;		// スクロールスピード
	static D3DXVECTOR3	m_ScrollPos;		// スクロール位置
	static int			m_nSpawnTimer;		// 敵のスポーン間隔
	bool				m_bNextMode;		// 二重押し防止変数

};


#endif //_RESULT_H