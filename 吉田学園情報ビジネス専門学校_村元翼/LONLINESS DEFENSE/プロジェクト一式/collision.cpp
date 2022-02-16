//=================================================
// �����蔻��̍쐬
// Author:���� ��
//=================================================
#include "collision.h"

//=================================================
// �R���X�g���N�^
//=================================================
CCollision::CCollision()
{

}

//=================================================
// �f�X�g���N�^
//=================================================
CCollision::~CCollision()
{

}

//=================================================
// ������
//=================================================
HRESULT CCollision::Init()
{
	return S_OK;
}

//=================================================
// �I��
//=================================================
void CCollision::Uninit()
{
	
}

//=================================================
// �X�V
//=================================================
void CCollision::Update()
{

}

//=================================================
// �ʏ퓖���蔻��
//=================================================
bool CCollision::SetCollision(CScene *pHit1, CScene *pHit2)
{
	D3DXVECTOR3 pos1;		// ����A�̈ʒu
	D3DXVECTOR3 pos2;		// ����B�̈ʒu
	D3DXVECTOR3 size1;		// ����A�̑傫��
	D3DXVECTOR3 size2;		// ����B�̑傫��

	pos1 = pHit1->GetPos();
	pos2 = pHit2->GetPos();
	size1 = pHit1->GetScale();
	size2 = pHit2->GetScale();

	D3DXVECTOR3 vec = pos2 - pos1;		// ��̈ʒu�̍��������߂�

	float fLength = sqrtf((vec.y * vec.y));
	float fLength2 = sqrtf((vec.x * vec.x));

	// �����蔻��̏���
	if (fLength <= size1.y &&
		fLength2 <= size1.x)
	{
		//���������Ƃ��������Ԃ�
 		return true;
	}

	// �������Ă��Ȃ�������false
	return false;

}

//=================================================
// �~�Ǝl�p�`�̓����蔻��
//=================================================
bool CCollision::CircleCollision(CScene *pCircle, CScene *pSquare)
{
	D3DXVECTOR3 CirclePos;		// �~�̈ʒu
	float		CircleRadius;	// �~�̔��a
	D3DXVECTOR3 SquarePos;		// ��`�̈ʒu
	D3DXVECTOR3 SquareRadius;	// ��`�̑傫��

	CirclePos = pCircle->GetPos();				// �ʒu(���S�_)�擾
	SquarePos = pSquare->GetPos();				// �ʒu(���S�_)�擾
	SquareRadius = (pSquare->GetScale() / 2);	// �l�p�`�̑傫���擾

	// x,y�̑傫���T�C�Y�𔼌a�Ɏ擾����
	if (pCircle->GetScale().x >= pCircle->GetScale().y)
	{
		CircleRadius = (pCircle->GetScale().x / 2);
	}

	else
	{
		CircleRadius = (pCircle->GetScale().y / 2);
	}

	//============================================//
	//			�㉺���E�̓����蔻��			  //
	//============================================//
	// �㉺
	if (CirclePos.x > (SquarePos.x - SquareRadius.x) && CirclePos.x < (SquarePos.x + SquareRadius.x) &&
		CirclePos.y >((SquarePos.y - SquareRadius.y) - CircleRadius) && CirclePos.y < ((SquarePos.y + SquareRadius.y) + CircleRadius)
		)
	{
		return true;
	}

	// ���E
	if (CirclePos.x > ((SquarePos.x - SquareRadius.x) - CircleRadius) && CirclePos.x < ((SquarePos.x + SquareRadius.x) + CircleRadius) &&
		CirclePos.y >(SquarePos.y - SquareRadius.y) && CirclePos.y < (SquarePos.y + SquareRadius.y)
		)
	{
		return true;
	}

	//======================================//
	//			�p�ۂ̓����蔻��			//
	//======================================//
	// ����
	if (pow((SquarePos.x - SquareRadius.x) - CirclePos.x, 2.0) + pow((SquarePos.y - SquareRadius.y) - CirclePos.y, 2.0) < pow(CircleRadius,2.0))
	{
		return true;
	}

	// �E��
	if (pow((SquarePos.x + SquareRadius.x) - CirclePos.x, 2.0) + pow((SquarePos.y - SquareRadius.y) - CirclePos.y, 2.0) < pow(CircleRadius, 2.0))
	{
		return true;
	}

	// �E��
	if (pow((SquarePos.x + SquareRadius.x) - CirclePos.x, 2.0) + pow((SquarePos.y + SquareRadius.y) - CirclePos.y, 2.0) < pow(CircleRadius, 2.0))
	{
		return true;
	}

	// ����
	if (pow((SquarePos.x - SquareRadius.x) - CirclePos.x, 2.0) + pow((SquarePos.y + SquareRadius.y) - CirclePos.y, 2.0) < pow(CircleRadius, 2.0))
	{
		return true;
	}

	// �������Ă��Ȃ�������
	return false;
}
