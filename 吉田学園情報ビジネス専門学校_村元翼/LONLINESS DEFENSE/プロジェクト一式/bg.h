//--------------------------------------
// �w�i
//--------------------------------------
#ifndef _BG_H
#define _BG_H
#include "scene2D.h"
#include "texture.h"

//-------------------------------------
// �O���錾
//-------------------------------------
class CScene;

//-------------------------------------
// �N���X����
//-------------------------------------
class CBg : public CScene2D
{
public:
	CBg(OBJTYPE nPriority = OBJTYPE_BG);
	~CBg();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBg *Create(bool bScrol = true,CTexture::Type type = CTexture::Bg, CScene::OBJTYPE objtype = CScene::OBJTYPE_BG); // �C���X�^���X��������
	void BgLimit(void);

	//-------------------------------------
	// Getter & Setter
	//-------------------------------------
	D3DXVECTOR3 GetTex(void)					{ return m_Tex; }
	D3DXVECTOR3 GetPos(void)					{ return m_pos; }
	static D3DXVECTOR2 GetRangeMin(void)		{ return m_SpreadRange_min; }
	static D3DXVECTOR2 GetRangeMax(void)		{ return m_SpreadRange_max; }

private:
	CTexture::Type				m_Type;			// �e�N�X�`���^�C�v
	D3DXVECTOR3					m_Tex;			// �e�N�X�`�����X�N���[������ϐ�
	D3DXVECTOR3					m_pos;			// �ʒu
	bool						m_bScroll;		// �X�N���[���؂�ւ�
	bool						m_bCanScroll;	// �X�N���[���\���ۂ�

	const static D3DXVECTOR2	m_SpreadRange_min;	// �w�i�̍L����傫��(�ŏ��l)
	const static D3DXVECTOR2	m_SpreadRange_max;	// �w�i�̍L����傫��(�ő�l)
};


#endif // !_BG_H

