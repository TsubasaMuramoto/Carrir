//--------------------------------------
// �`���[�g���A���̏���
//--------------------------------------
#ifndef _TUTORIAL_H
#define _TUTORIAL_H
#include "main.h"
#include "scene.h"

//--------------------------------------
// �}�N����`
//--------------------------------------
#define MAX_TUTORIAL_POLYGON (5)

//--------------------------------------
//�O���錾
//--------------------------------------
class CBg;
class CScene2D;

//----------------------------------------
// �`���[�g���A���N���X�̍쐬
//----------------------------------------
class CTutorial
{
public:

	CTutorial();
	~CTutorial();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void NextMode(bool bNextMode) { m_bNextMode = bNextMode; }

private:
	CScene2D			*m_pTutorial[2];	// �y�[�W���̃`���[�g���A���|���S��		
	bool				m_bNextMode;		// ���̃��[�h�ɍs�����߂�
};


#endif //_TITLE_H