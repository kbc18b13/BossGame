#pragma once
#include "..\SkeletonEnemy.h"
#include "Act.h"

namespace SkeletonAct{

class Chase : public Act{
public:
	Chase();
	virtual ~Chase();

	void Start( SkeletonEnemy* s ) override;
	void Update( SkeletonEnemy* s ) override;

private:
	float m_timer = 0;
};

}