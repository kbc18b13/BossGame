#pragma once
#include "physics/ICollider.h"
#include "physics/CollisionAttr.h"
#include "ActorHitCollision.h"

class Actor;

class Weapon{
public:
	void Init(Actor* master, ICollider& collider, EnCollisionAttr target);

	void Update();

	void UpdateWorldMatrix(CMatrix mat );

	void AttackStart(){
		m_isAttack = true;
		m_hitActors.clear();
	}
	void AttackEnd(){
		m_isAttack = false;
	}

	void SetActive( bool active ){
		m_collision.SetActive( active );
	}

	void SetOffset( const CVector3& offset ){
		m_collision.SetOffset( offset );
	}

	void SetDamage( UINT damage ){
		m_damage = damage;
	}

	void SetKnockBack( const CVector3 knock ){
		m_knock = knock;
	}

private:
	ActorHitCollision m_collision;

	UINT m_damage = 1;
	CVector3 m_knock;

	std::vector<Actor*> m_hitActors;

	Actor* m_master;

	bool m_isAttack = false;
};

