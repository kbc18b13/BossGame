#pragma once
#include "Act.h"

class Player;

class ActChase : public Act {
public:
	ActChase();

	void Start() override;
    void Continue(ActArg& arg);

private:
	float m_timer = 0.0f;
};