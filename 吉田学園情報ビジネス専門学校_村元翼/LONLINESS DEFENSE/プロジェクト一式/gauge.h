//-----------------------------------------------------
//�Q�[�W����
//-----------------------------------------------------
#ifndef _GAUGE_H_
#define _GAUGE_H_
#include "scene.h"
#include "scene2D.h"
#include "texture.h"

//-----------------------------------------------------
// �}�N����`
//-----------------------------------------------------
#define MAX_GAUGE_WIDTH (400.0f)

//-----------------------------------------------------
// �N���X�̐���
//-----------------------------------------------------
class CGauge : public CScene2D
{
public:
	CGauge(OBJTYPE nPriority = OBJTYPE_POLYGON);
	~CGauge();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGauge *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	static void SetGauge(float Set);				// �Q�[�W�̑���

private:
	D3DXVECTOR3			m_pos;						// �ʒu
	static D3DXVECTOR3	m_Scale;					// �Q�[�W�̑傫��
	float				m_fScaleSpeed;				// �Q�[�W�𑝂₵�Ă���
	bool				m_bNextMode;				// ��d�����h�~�ϐ�
	bool				m_bOneTimeOnlyPlay;			// 

};

#endif // !_TIME_H_*/#pragma once
