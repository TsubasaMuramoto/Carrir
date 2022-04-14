//--------------------------------------
//�^�C�g���̏���
//--------------------------------------
#ifndef _GAME_H
#define _GAME_H
#include "main.h"
#include "scene.h"

//---------------------------------------
// �O���錾
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
// �N���X�̐���
//------------------------------
class CGame
{
public:

	//--------------------------
	// ���x���Ǘ��\����
	//--------------------------
	typedef enum
	{
		FROM_NONE = 0,
		FROM_UP,		// ��
		FROM_DOWN,		// ��
		FROM_LEFT,		// ��
		FROM_RIGHT,		// �E
		FROM_MAX
	}POP_FROM;

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
	static CBg							*GetBg(void)					{ return m_pBg; }
	static CGauge						*GetGauge(void)					{ return m_pGauge; }
	static CPolygon						*GetMiniMap(void)				{ return m_pMiniMap; }
	static CMiniPolygon					*GetMiniPolygon(void)			{ return m_pMiniPlayer; }
	static D3DXVECTOR3					GetScroll(void)					{ return m_ScrollSpeed; }
	static D3DXVECTOR3					GetScrollPos(void)				{ return m_ScrollPos; }
	static int							GetTimer(void)					{ return m_nSpawnTimer; }
	static void							SetScroll(D3DXVECTOR3 scroll)	{ m_ScrollSpeed = scroll; }
	static void							SetScroll(const char* Direction,D3DXVECTOR3 speed);

private:
	//-----------------------------
	// Game�N���X�Ŏg�p����N���X
	//-----------------------------
	static CScene2D						*m_pGaugeFrame;
	static CScore						*m_pScore;
	static CBg							*m_pBg;
	static CPlayer						*m_pPlayer;
	static CTime						*m_pTime;
	static CPolygon						*m_pMiniMap;
	static CTarget						*m_pTarget;
	static CGauge						*m_pGauge;
	static CMiniPolygon					*m_pMiniPlayer;

	static D3DXVECTOR3	m_ScrollSpeed;		// �X�N���[���X�s�[�h
	static D3DXVECTOR3	m_ScrollPos;		// �X�N���[���ʒu
	static int			m_nSpawnTimer;		// �G�̃X�|�[���Ԋu
	bool				m_bNextMode;		// ��d�����h�~�ϐ�
};
#endif //_RESULT_H