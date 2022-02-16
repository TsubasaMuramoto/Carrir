//--------------------------------------------------
// �G�t�F�N�g�̍쐬
// Author
//--------------------------------------------------
#ifndef _EFFECT_H_
#define _EFFECT_H_
#include "texture.h"
#include "scene.h"
#include "scene2D.h"

//---------------------------------------------------------------
// �O���錾
//---------------------------------------------------------------

//---------------------------------------------------------------
// �G�t�F�N�g�N���X(�V�[��2D�̔h��)
//---------------------------------------------------------------
class CEffect : public CScene2D
{
public:

	//-------------------------------------------
	// �G�t�F�N�g�^�C�v�\����
	//-------------------------------------------
	typedef enum
	{
		EFFECT_NORMAL = 0,	// ����
		EFFECT_BULLET,		// �e
		EFFECT_PLAYER,		// �v���C���[
		EFFECT_EXPLOSION,	// ����
		EFFECT_MAX			// �ő�

	}EFFECT_TYPE;

	CEffect(OBJTYPE OBJTYPE_EFFECT);
	~CEffect();

	HRESULT Init(CTexture::Type type);
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	/* �ʒu�̐ݒ�,�ړ���,�T�C�Y,�F�ݒ�,�������Ȃ�X�s�[�h,Texture */
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 m_move, D3DXVECTOR3 size, D3DXCOLOR col, float ScaleSpeed, float TransparentSpeed, float angle, EFFECT_TYPE effectType, CTexture::Type type = CTexture::Effect);
	void ProcessByType(EFFECT_TYPE type);
	void RandomInjection(void);									// ��������Ƀ����_�����˂���G�t�F�N�g
	void EffectAnim(int &nAnimCounter, int nSpan, D3DXVECTOR2 &Pattern,D3DXVECTOR2 MaxPattern);

private:

	EFFECT_TYPE		m_EffectType;			// �G�t�F�N�g�^�C�v
	D3DXVECTOR3		m_pos;					// �ʒu
	D3DXVECTOR3		m_posOld;				// �Ō�̈ʒu
	D3DXVECTOR3		m_move;					// �ړ���
	D3DXVECTOR3		m_size;					// �傫��
	D3DXCOLOR		m_col;					// �F
	D3DXVECTOR2		m_Pattern;				// �A�j���[�V�����p�^�[��
	int				m_nAnimCounter;			// �A�j���[�V�����J�E���^�[
	int				m_nLife;				// ����
	float			m_fAngle;				// �p�x
	float			m_fScaleSpeed;			// �T�C�Y�����������鑬�x
	float			m_fTransparentSpeed;	// ���߂��鑬�x
	bool			m_bDoOnce;				// ��x�����ʂ�����
	bool			m_bUse;					// �g�p����

};
#endif // !_EFFECT_H_

