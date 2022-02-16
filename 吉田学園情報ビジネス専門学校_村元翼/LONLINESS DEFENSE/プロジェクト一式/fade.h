//-----------------------------------------------------
//�t�F�[�h�̏���
//-----------------------------------------------------
#ifndef _FADE_H_
#define _FADE_H_
#include "texture.h"
#include "manager.h"
#include "scene2D.h"

//-----------------------------------------------------
// �O���錾
//-----------------------------------------------------
class CBg;

//-----------------------------------------------------
// �N���X�錾
//-----------------------------------------------------
class CFade : public CScene
{
public:
	//----------------------------------
	// �t�F�[�h�̏�ԍ\����
	//----------------------------------
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX,
	} FADE;

	CFade(OBJTYPE nPriority = OBJTYPE_FADE);
	~CFade();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetFade(CManager::MODE modeNext);						// �t�F�[�h�̐ݒ�
	FADE GetFade(void);													// �t�F�[�h�̎擾
	static CFade *Create(CTexture::Type type,CManager::MODE modeNext);	// �C���X�^���X��������

private:
	CTexture::Type				m_Type;			// �e�N�X�`���^�C�v
	static CBg					*m_pBg;			// �w�i�N���X
	static FADE					m_fade;			// �t�F�[�h�̏��
	static CManager::MODE		m_modeNext;		// ���̉�ʁi���[�h�j
	static float				m_colorAlpha;	// �t�F�[�h�̐F

};
#endif // !_FADE_H_

