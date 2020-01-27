#pragma once
#include "physics/BoxCollider.h"
#include "Weapon.h"
class SkinModelRender;
class Actor;

class ModelArmWeapon{
public:
	ModelArmWeapon();
	~ModelArmWeapon();

	void Init( Bone* handBone, Actor* master, const CVector3& halfExtents,
			   const wchar_t* modelpath, bool isPlayers );

	void SetOffset( const CVector3& offset ){
		m_weapon.SetOffset( offset );
	}
	void Update();

	void AttackStart(){
		m_weapon.AttackStart();
	}
	void AttackEnd(){
		m_weapon.AttackEnd();
	}

	void SetDamage( UINT damage ){
		m_weapon.SetDamage( damage );
	}

	void SetKnockBack( const CVector3& knock ){
		m_weapon.SetKnockBack( knock );
	}

	void SetActive( bool active ){
		m_weapon.SetActive( active );
		m_model.SetActive( active );
	}

private:

	Bone* m_hand; //手のボーン

	Actor* m_master;

	SkinModelRender m_model;
	BoxCollider		m_collider;				//コライダー。
	Weapon          m_weapon;

	bool m_isPlayers;
};

