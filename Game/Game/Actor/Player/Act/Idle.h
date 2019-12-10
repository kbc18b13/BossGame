#pragma once
#include "Act.h"

namespace PlayerAct{

class Idle : public Act{
public:
	Idle();
	~Idle();

	void ChangeState( ActArg& arg ) override;

	void Update( ActArg& arg ) override;
};

}