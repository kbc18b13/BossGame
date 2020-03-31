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

	void SetModelOffset( const CVector3& offset ){
		m_modelOffset = offset;
	}

	void SetModelRot( const CQuaternion& rot ){
		m_modelRot = rot;
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

	SkinModelRender& GetModel(){
		return m_model;
	}

	void SetSound( SoundOverlap* sound ){
		m_weapon.SetSound( sound );
	}

private:

	Bone* m_hand; //手のボーン

	Actor* m_master;

	SkinModelRender m_model;
	BoxCollider		m_collider;				//コライダー。
	Weapon          m_weapon;

	CVector3 m_modelOffset;
	CQuaternion m_modelRot;

	bool m_isPlayers;
};

