#pragma once
#include "PlayerAct.h"

namespace PlayerSpace{

class Damage : public PlayerAct{
public:
	Damage();
	~Damage();

	void SubStart( Actor* p ) override;

	void Update( Actor* p ) override;
};

}

