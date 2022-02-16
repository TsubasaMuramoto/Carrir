//=============================================================================
//
// �G����
// Author : ������
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "scene2D.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ENEMY_SIZE (D3DXVECTOR3(50.0f,50.0f,0.0f))
#define ENEMY_SPEED (D3DXVECTOR3(2.0f,2.0f,0.0f))

//=============================================================================
// �O���錾
//=============================================================================
class CTexture;
class CMiniPolygon;

//=============================================================================
// �N���X
//=============================================================================
class CEnemy : public CScene2D
{
public:
	CEnemy(OBJTYPE nPriority = OBJTYPE_ENEMY);		// �R���X�g���N�^
	~CEnemy();										// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, CTexture::Type texture = CTexture::Enemy);
	void Move(void);
	void SetPos(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void)		{ return m_pos; }
	D3DXVECTOR3 GetScale(void)		{ return m_scale; }
	D3DXVECTOR3 GetMove(void)		{ return m_move; }
	static int	GetAll(void)		{ return m_nAll; }
	void FeaturedTarget(D3DXVECTOR3 *targetPos, D3DXVECTOR3 *featuredPos);				// �^�[�Q�b�g�Ɍ�������

private:
	int				nFrame = 0;
	int				nPattern = 0;
	int				m_nLife;
	bool			m_bUse;
	D3DXVECTOR3		m_pos;
	D3DXVECTOR3		m_scale;
	D3DXVECTOR3		m_move;
	D3DXVECTOR3		m_Speed;
	CTexture::Type	m_Tex;
	CMiniPolygon	*m_pMiniEnemy;
	static int		m_nAll;
};
#endif // _ENEMY_H_
