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
#define MAX_GAUGE_WIDTH (400.0f)					// �Q�[�W��
#define DECREASE_GAUGE (-30.0f)						// �Q�[�W�̌����
#define GAUGE_POS (D3DXVECTOR3(50.0f,50.0f,0.0f))	// �Q�[�W�ʒu

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

	static CGauge *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);	// ����
	static void SetGauge(float Set);							// �Q�[�W�̑���

private:
	D3DXVECTOR3			m_pos;									// �ʒu
	static D3DXVECTOR3	m_Scale;								// �Q�[�W�̑傫��
	bool				m_bNextMode;							// ��d�����h�~�ϐ�

};

#endif // !_TIME_H_
