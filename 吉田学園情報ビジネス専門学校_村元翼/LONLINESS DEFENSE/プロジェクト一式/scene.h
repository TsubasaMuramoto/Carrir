//----------------------------------
//�I�u�W�F�N�g�̏���
//----------------------------------
#ifndef _SCENE_H_
#define _SCENE_H_
#include "main.h"

//----------------------------------
// �N���X�錾
//----------------------------------
class CScene
{
public:

	//----------------------------------------------------
	// �I�u�W�F�N�g�̃^�C�v�\����
	//----------------------------------------------------
	typedef enum
	{
		OBJTYPE_NONE = 0,			// �Ȃ�
		OBJTYPE_BG,					// �w�i
		OBJTYPE_TARGET,				// �^�[�Q�b�g
		OBJTYPE_ENEMY,				// �G
		OBJTYPE_BULLET,				// �e
		OBJTYPE_FIELD,				// ��
		OBJTYPE_EFFECT,				// �G�t�F�N�g
		OBJTYPE_PLAYER,				// �v���C���[
		OBJTYPE_POLYGON,			// �|���S��
		OBJTYPE_NUMBER,				// �i���o�[
		OBJTYPE_UI,					// UI
		OBJTYPE_PAUSE,				// �|�[�Y
		OBJTYPE_FADE,				// �t�F�[�h
		OBJTYPE_MAX
	}OBJTYPE;

	CScene();
	explicit CScene(OBJTYPE nPriority);
	virtual~CScene();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	//-----------------------------
	// Getter & Setter
	//-----------------------------
	void SetObjType(OBJTYPE objType)	{ m_ObjType = objType; }
	void SetPos(D3DXVECTOR3 pos)		{ m_pos = pos; }
	void SetScale(D3DXVECTOR3 Scale)	{ m_Scale = Scale; }
	void SetMove(D3DXVECTOR3 move)		{ m_move = move; }
	void SetTex(D3DXVECTOR2 tex)		{ m_Tex = tex; }
	void LifeSub(int nPow);

	int GetLife(void)					{ return m_nLife; }
	CScene::OBJTYPE GetObjType(void)	{ return m_ObjType; }
	D3DXVECTOR3 GetPos(void)			{ return m_pos; }
	D3DXVECTOR3 GetScale(void)			{ return m_Scale; }
	D3DXVECTOR3 GetMove(void)			{ return m_move; }
	D3DXVECTOR2 GetTex(void)			{ return m_Tex; }
	bool GetDamage(void)				{ return m_bDamage; }
	bool GetDeath(void)					{ return m_bDeath; }

	static CScene *GetScene(const int nPriority)	{ return m_pTop[nPriority]; }
	static CScene *GetSceneNext(CScene *pTop)		{ return pTop->m_pNext; }

	static void ReleaseAll(void);	// �S�ẴC���X�^���X�̔j������
	static void UpdateAll(void);	// �S�ẴI�u�W�F�̍X�V	
	static void DrawAll(void);		// �S�ẴI�u�W�F�̕`��
	
private:
	D3DXVECTOR3				m_pos,m_oldpos;					// ��̈ʒu
	D3DXVECTOR3				m_move;							// �ړ���
	D3DXVECTOR3				m_Scale;						// �傫��
	D3DXVECTOR2				m_Tex;							// �e�N�X�`���̑傫��
	OBJTYPE					m_ObjType;						// �I�u�W�F�N�g�^�C�v�̎��
	static int				m_nNumAll[OBJTYPE_MAX];			// �^�C�v���Ƃ̃I�u�W�F��
	int						m_nID;							// �i�[��̔ԍ�
	int						m_nLife;						// ���C�t
	int						m_nPriority;					// �D�揇��
	bool					m_bDamage;						// �_���[�W����

	static CScene			*m_pTop[OBJTYPE_MAX];			// �擪�̃I�u�W�F�N�g�̃|�C���^
	static CScene			*m_pCur[OBJTYPE_MAX];			// ���݁i��Ԍ��j�̃I�u�W�F�N�g�̃|�C���^
	CScene					*m_pPrev;						// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene					*m_pNext;						// ���̃I�u�W�F�N�g�ւ̃|�C���^
	bool					m_bDeath;

protected:
	void Release(void);//�I�u�W�F�N�g�P�̂̃C���X�^���X�j��

};
#endif // !_SCENE_H_
