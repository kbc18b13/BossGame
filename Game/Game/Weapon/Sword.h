#pragma once
#include "physics/BoxCollider.h"
#include "physics/CollisionObject.h"
class SkinModelRender;
class Actor;

class Sword{
public:
	Sword();
	~Sword();

	void Init( Bone* handBone, Actor* master, const CVector3& halfExtents,
			   const wchar_t* modelpath, bool playersSword);

	void SetOffset( const CVector3& offset ){
		m_offset = offset;
	}
	void Update();

	void SlashStart();
	void SlashEnd();

	void SetDamage( UINT damage ){
		m_damage = damage;
	}

	void SetActive( bool active );

	void SetCool( float cooltime ){
		m_coolTime = cooltime;
	}

private:

	Bone* m_hand; //��̃{�[��

	Actor* m_master;

	SkinModelRender m_model;
	BoxCollider		 m_collider;				//�R���C�_�[�B
	CollisionObject  m_collision;              //�R���W�����B
	CVector3 m_offset; //�ʒu�I�t�Z�b�g

	bool m_isSlash = false;  //�U�����Ȃ�true
	UINT m_damage = 1;
	float m_coolTime = 0.5f;

	bool m_isPlayers;

	bool m_isActive = true;
};