//--------------------------------------
// ���U���g�̏���
//--------------------------------------
#ifndef _RESULT_H
#define _RESULT_H
#include "main.h"
#include "scene.h"

//--------------------------------------
// �}�N����`
//--------------------------------------
#define MAX_RESULT				(4)
#define RESULT_RANKING_POSY		(60.0f)			// �����L���O��Y���W

//--------------------------------------
// �O���錾
//--------------------------------------
class CBg;
class CPolygon;
class CRanking;

//--------------------------------------
// ���U���g�N���X�̐���
//--------------------------------------
class CResult
{
public:

	//--------------------------------------
	// �I�����\����
	//--------------------------------------
	typedef enum
	{
		GAME_RETRY = 0,
		TITLE,
		MAX,
	}TYPE;

	//--------------------------------------
	// ���\�b�h
	//--------------------------------------
	CResult();
	~CResult();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void NextMode(bool bNextMode) { m_bNextMode = bNextMode; }

private:
	CPolygon			*pPolygon[MAX_RESULT];			// �|���S���N���X(�I������\��)
	CPolygon			*m_Cursol;						// �|���S���N���X(�J�[�\����\��)
	CRanking			*m_pRanking;					// �����L���O�̃|�C���^

	bool				m_bNextMode;					// ���̃��[�h�ɍs�����߂�bool�ϐ�
	int					m_nSelectType;					// ���݂̑I��

};


#endif //_RESULT_H