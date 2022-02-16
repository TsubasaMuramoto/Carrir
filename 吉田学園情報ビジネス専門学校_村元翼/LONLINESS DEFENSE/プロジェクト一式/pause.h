//--------------------------------------
// PAUSE�̏���
// Author: 
//--------------------------------------
#ifndef _PAUSE_H
#define _PAUSE_H
#include "main.h"
#include "scene.h"
#include "texture.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define MAX_PAUSE (3)
#define PAUSE_INERVAL (100.0f)
#define SELECT_HEIGHT (300.0f)
#define SELECT_SIZE (D3DXVECTOR3(350.0f,60.0f,0.0f))

//-------------------------------------------
// �O���錾
//-------------------------------------------
class CPolygon;
class CScene2D;
class CBg;

//---------------------------------------------
// �|�[�Y�̃N���X
//---------------------------------------------
class CPause : public CScene
{
public:
	//-----------------------------------------
	// �|�[�Y�t�F�[�h�̏�ԍ\����
	//-----------------------------------------
	typedef enum
	{
		FADE_IN = 0,
		FADE_OUT,
	}PAUSE_FADE;

	CPause(OBJTYPE nPriority = OBJTYPE_PAUSE);
	~CPause();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPause *Create(D3DXVECTOR3 pos);			// �C���X�^���X��������

private:
	//void FadeInOut(int nFade);						// �|�[�Y�̃t�F�[�h�Ɏg���֐��H
	//void SetPAUSE(int nType);						// PAUSE�Ɏg���|���S���̐����H
	D3DXVECTOR3		m_pos;							// �ʒu
	D3DXVECTOR3		m_Speed;						// ���x
	float			m_fAlpha;						// �|�[�Y�w�i�̓����x
	int				m_nPauseType;					// �|�[�Y�I��
	bool			m_bUninit;						// pause���I�������邩
	bool			m_bNextMode;					// ���̃��[�h�ɂ�����
	CScene2D		*m_pPolygon[MAX_PAUSE];			// �|�[�Y�I���̃|���S��
	CScene2D		*m_pCursor;						// �I���J�[�\���̃|���S��
	CScene2D		*m_pTutorialUI;					// �������UI
	static CBg		*m_pBg;							// �|�[�Y�w�i

};


#endif //_PAUSE_H