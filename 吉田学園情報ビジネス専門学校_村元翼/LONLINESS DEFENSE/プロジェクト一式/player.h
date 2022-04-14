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
// �}�N����`
//=============================================================================
#define MAX_SPEED		(10.0f)														// �ő呬�x
#define SHOOT_INTERVAL	(0.5f)														// �e���ˊԊu
#define INERTIA_SPEED	(0.2f)														// �������x(����and����)
#define PLAYER_POS		(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))	// �v���C���[�ʒu
#define PLAYER_SIZE		(D3DXVECTOR3(40.0f, 40.0f, 0.0f))							// �v���C���[�T�C�Y

//=============================================================================
// �O���錾
//=============================================================================
class CXInput;

//=============================================================================
// �N���X�̐���
//=============================================================================
class CPlayer : public CScene2D
{
public:

	// �ړ�����
	typedef enum
	{
		DIRECTION_UP = 0,	// ��
		DIRECTION_DOWN,		// ��
		DIRECTION_LEFT,		// ��
		DIRECTION_RIGHT,	// �E
		DIRECTION_NO_UP,	// �㖳
		DIRECTION_NO_DOWN,	// ����
		DIRECTION_NO_LEFT,	// ����
		DIRECTION_NO_RIGHT,	// �E��
		DIRECTION_MAX

	}MOVE_DIRECTION;


	CPlayer(OBJTYPE nPriority = OBJTYPE_PLAYER);		// �R���X�g���N�^
	~CPlayer();											// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, CTexture::Type texture = CTexture::Player);

	void Move(void);																// �v���C���[�̈ړ��֐�
	void MovingLimit(D3DXVECTOR3& pos, D3DXVECTOR3 &scale, D3DXVECTOR3 &speed);		// �ړ����E�ݒ�֐�
	void Rotate(D3DXVECTOR3 pos, D3DXVECTOR3 scale, float Angle);					// ��]�֐�
	void Acceleration(D3DXVECTOR3 &velo, D3DXVECTOR3 &speed,const float &Maxspeed);	// �����֐�
	float RotateGamePad(CXInput *pXInput);											// �Q�[���p�b�h�ł̉�]�֐�
	float FeaturedMouse(D3DXVECTOR3 pos, POINT mousePoint);							// �}�E�X�Ǐ]�����֐�
	bool InputDirection(const MOVE_DIRECTION &moveDir);							// �ړ��������͊֐�

	//-------------------------
	// Getter & Setter
	//-------------------------
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

	const static D3DXVECTOR2 m_ScrollRange;	// �X�N���[�������W
	const static D3DXVECTOR2 m_ScrollRange2;// �X�N���[�������W
};

#endif // _PLAYER_H_
