#pragma once
#include "Act.h"

namespace PlayerAct{

class Walk : public Act{
public:
	Walk();
	~Walk();

	void ChangeState( Player* p ) override;

	void Update( Player* p ) override;

};

}