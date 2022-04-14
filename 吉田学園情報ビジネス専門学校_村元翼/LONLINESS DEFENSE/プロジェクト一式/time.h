//---------------------------------------------------------------
// �^�C���̍쐬
//---------------------------------------------------------------
#ifndef _TIME_H_
#define _TIME_H_
#include "scene.h"
#include "texture.h"

//---------------------------------------------------------------
// �}�N����`
//---------------------------------------------------------------
#define MAX_TIME		(3)											 // �`�悷��|���S������
#define TIME_LIMIT		(60)										 // ��������
#define TIME_REDZONE	(TIME_LIMIT / 3)							 // �������Ԃ̃��b�h�]�[��
#define TIME_FRAME		(60)										 // �ő�t���[��
#define TIME_SIZE		(D3DXVECTOR3(50.0f, 50.0f, 0.0f))			 // �^�C���T�C�Y
#define TIME_POS		(D3DXVECTOR3(SCREEN_WIDTH / 2, 40.0f, 0.0f)) // �^�C���ʒu

//---------------------------------------------------------------
// �O���錾
//---------------------------------------------------------------
class CNumber;

//---------------------------------------------------------------
// �^�C���N���X(�V�[���̔h��)
//---------------------------------------------------------------
class CTime : public CScene
{
public:
	CTime(OBJTYPE nPriority = OBJTYPE_NUMBER);
	~CTime();

	static CTime *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);// ����
	HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 size);			// ������
	HRESULT Init();											// ������
	void Uninit(void);										// �I��
	void Update(void);										// �X�V
	void Draw(void);										// �`��
	void SetTime(void);										// �`�悳��Ă���e�N�X�`���̐ݒ�

private:
	int		m_nTime;									// ���݂̎���
	int		m_nFrame = 0;								// �t���[����
	int		m_nAll;										// �^�C���|���S����
	bool	m_bNextMode;								// ���̃��[�h�ɍs�����߂̕ϐ�
	CNumber *m_apNumber[MAX_TIME];						// �^�C���Ɏg���|���S��
};

#endif // !_TIME_H_*/


