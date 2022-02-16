//=============================================================================
//
// �v���C���[�̏���
// Author : ������
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "scene2D.h"

//=============================================================================
// �O���錾
//=============================================================================
class CTexture;
class CBullet;
class CXInput;

//=============================================================================
// �N���X�̐���
//=============================================================================
class CPlayer : public CScene2D
{
public:

	CPlayer(OBJTYPE nPriority = OBJTYPE_PLAYER);		// �R���X�g���N�^
	~CPlayer();											// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, CTexture::Type texture = CTexture::Player);

	void Move(void);
	void MovingLimit(D3DXVECTOR3& pos, D3DXVECTOR3 &scale, D3DXVECTOR3 &speed);
	void Rotate(D3DXVECTOR3 pos, D3DXVECTOR3 scale, float Angle);
	void Acceleration(D3DXVECTOR3& vec, D3DXVECTOR3 speed, float Maxspeed);
	float RotateGamePad(CXInput *pGamePad);
	float FeaturedMouse(D3DXVECTOR3 pos, POINT mousePoint);

	// �Z�b�^�[�ƃQ�b�^�[
	void SetPos(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void)			{ return m_pos; }
	D3DXVECTOR3 GetScale(void)			{ return m_scale; }
	D3DXVECTOR3 GetSpeed(void)			{ return m_Speed; }


private:
	D3DXVECTOR3			m_pos;				// �ʒu
	D3DXVECTOR3			m_scale;			// �傫��
	D3DXVECTOR3			m_rot;				// ��]
	D3DXVECTOR3			m_velocity;			// pos�𓮂����ϐ�
	D3DXVECTOR3			m_Direction;		// ����
	D3DXVECTOR3			m_Speed;			// ���x
	D3DXVECTOR3			m_RotateVertex[4];	// ��]�Ɏg�����_���W
	CTexture::Type		m_Tex;				// �e�N�X�`��
	float				m_fMaxSpeed;		// �ō����x
	float				m_fAngle;			// �p�x
	float				m_fShootInterval;	// �ˌ��Ԋu
	POINT				m_Point;			// �J�[�\�����

	const static D3DXVECTOR2 m_ScrollRange;
	const static D3DXVECTOR2 m_ScrollRange2;
};

#endif // _PLAYER_H_
