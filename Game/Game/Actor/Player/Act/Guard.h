#pragma once
#include "PlayerAct.h"

namespace PlayerSpace{

class Guard : public PlayerAct{
public:
	Guard();
	~Guard();

	void Update( Actor* p ) override;
};

}

