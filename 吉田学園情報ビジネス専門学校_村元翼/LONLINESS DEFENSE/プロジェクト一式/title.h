//--------------------------------------
//�^�C�g���̏���
//--------------------------------------
#ifndef _TITLE_H
#define _TITLE_H
#include "main.h"
#include "scene.h"

//--------------------------------------
//�}�N����`
//--------------------------------------
#define MAX_TITLE_POLYGON (2)
#define BLINK_INTERVAL (60)

//--------------------------------------
//�O���錾
//--------------------------------------
class CBg;
class CScene2D;

//----------------------------------------
// �^�C�g���N���X�̍쐬
//----------------------------------------
class CTitle
{
public:
	typedef enum
	{
		GAME_START = 0,
		OPERATION,
		MAX,
	}TYPE;

	CTitle();
	~CTitle();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void NextMode(bool bNextMode) { m_bNextMode = bNextMode; }

private:
	CScene2D			*m_pTitle[MAX_TITLE_POLYGON];	// �V�[��2D�N���X
	int					m_nSelectType;					// �I�������^�C�v
	int					m_nFrame;						// �t���[����
	int					m_nMultiFrame;					// �t���[�����Ɋ|���鐔
	bool				m_bNextMode;					// ���̃��[�h�ɍs�����߂�
};


#endif //_TITLE_H