#pragma once
#include "Act.h"

namespace PlayerAct{

class Idle : public Act{
public:
	Idle();
	~Idle();

	void ChangeState( Player* p ) override;

	void Update( Player* p ) override;
};

}