#pragma once
#include "..\SkeletonEnemy.h"
#include "Act.h"

namespace SkeletonAct{

class Attack : public Act{
public:
	Attack(SkeletonEnemy::Anim anim, SkeletonEnemy::Anim next );
	virtual ~Attack();

	void Start( SkeletonEnemy* s ) override;
	void Update( SkeletonEnemy* s ) override;

private:
	int m_anim;
	SkeletonEnemy::Anim m_next;
};

}

