#pragma once
#include "PlayerAct.h"

namespace PlayerSpace{

class JumpAtk : public PlayerAct{
public:
	JumpAtk();

	void SubStart( Actor* p ) override;

	void Update( Actor* p ) override;

	void End( Actor * p ) override;
};

}
