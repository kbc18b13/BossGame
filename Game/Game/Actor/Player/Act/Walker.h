#pragma once
#include "PlayerAct.h"

namespace PlayerSpace{

class Walker : public PlayerAct{
public:
	Walker();
	~Walker();

	void Update( Actor* p ) override;
};

}