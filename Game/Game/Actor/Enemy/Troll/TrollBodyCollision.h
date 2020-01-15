#pragma once
#include "physics/CylinderCollider.h"
#include "Util/ActorHitCollision.h"

class Troll;

class TrollBodyCollision{
public:
	TrollBodyCollision();
	~TrollBodyCollision();

	void Init( Troll* troll );
	void Update();

	void StartAttack(){
		isAttack = true;
	}
	void EndAttack(){
		isAttack = false;
	}

	void SetActive( bool active ){
		m_collision.SetActive( active );
		isAttack = false;
	}

private:
	UINT damage = 3;
	float coolTime = 3.0f;

	bool isAttack = false;

	Troll* m_master = nullptr;

	CylinderCollider m_shape; //“–‚½‚è”»’è‚ÌŒ`

	ActorHitCollision m_collision;
};