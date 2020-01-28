#pragma once
#include "PlayerAct.h"

namespace PlayerSpace{

class Idle : public PlayerAct{
public:
	Idle();
	~Idle();

	void Update( Actor* p ) override;
};

}