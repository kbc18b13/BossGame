#pragma once
#include "Act.h"

class TrollArmCollision;

class ActAttack : public Act {
public:
	ActAttack(TrollArmCollision& arm);
	void Start() override;
	void Continue(ActArg& arg) override;

private:
    bool m_isAttack = false;
	float m_timer = 0.0f;
    TrollArmCollision& m_arm;
};