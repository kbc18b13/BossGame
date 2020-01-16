#pragma once
#include "..\SkeletonEnemy.h"
#include "Act.h"

namespace SkeletonAct{

class Idle : public Act{
public:
	Idle();
	virtual ~Idle();

	void Start( SkeletonEnemy* s ) override;
	void Update( SkeletonEnemy* s ) override;

private:
	float m_timer;
};

}

