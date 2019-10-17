#pragma once
#include "Act.h"

class ActAttack : public Act {
public:
	ActAttack();
	void Start() override;
	void Continue(ActArg& arg) override;

private:
	float m_timer = 0.0f;
};