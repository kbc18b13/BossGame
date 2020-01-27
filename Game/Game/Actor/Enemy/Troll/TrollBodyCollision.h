#pragma once
#include "physics/CylinderCollider.h"
#include "Weapon/Weapon.h"

class Troll;

class TrollBodyCollision{
public:
	TrollBodyCollision();
	~TrollBodyCollision();

	void Init( Troll* troll );
	void Update();

	void StartAttack(){
		m_weapon.AttackStart();
	}
	void EndAttack(){
		m_weapon.AttackEnd();
	}

	void SetActive( bool active ){
		m_weapon.SetActive( active );
	}

private:
	CylinderCollider m_shape; //“–‚½‚è”»’è‚ÌŒ`
	Weapon m_weapon;
	Troll* m_master = nullptr;
};