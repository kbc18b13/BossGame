#pragma once
#include "PlayerAct.h"

namespace PlayerSpace{

class Walk : public PlayerAct{
public:
	Walk();
	~Walk();

	void Update( Actor* p ) override;

};

}