//=================================================
// �����蔻��̍쐬
// Author:���� ��
//=================================================

//=================================================
// �C���N���[�h�t�@�C�� �� �O���錾
//=================================================
#include "main.h"
#include "scene2D.h"
#include "scene.h"

//=================================================
// �}�N����`
//=================================================
#define _OX_EPSILON_ 0.000001f	// �덷

//=================================================
// �N���X�̍쐬
//=================================================
class CCollision
{
public:
	CCollision();
	~CCollision();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	bool SetCollision(CScene *pHit1,CScene *pHit2);
	bool CircleCollision(CScene *pCircle, CScene *pSquare);

private:

};

// �����蔻��ɕK�v�Ȃ���