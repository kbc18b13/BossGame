#pragma once
#include "Act.h"

namespace PlayerAct{

class Guard : public Act{
public:
	Guard();
	~Guard();

	void ChangeState( Player* p ) override;

	void Update( Player* p ) override;
};

}

