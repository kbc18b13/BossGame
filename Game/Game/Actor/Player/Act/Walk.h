#pragma once
#include "Act.h"

namespace PlayerAct{

class Walk : public Act{
public:
	Walk();
	~Walk();

	void ChangeState( ActArg& arg ) override;

	void Update( ActArg& arg ) override;

};

}