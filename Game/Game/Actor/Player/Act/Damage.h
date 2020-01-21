#pragma once
#include "Act.h"

namespace PlayerAct{

class Damage : public Act{
public:
	Damage();
	~Damage();

	void Start( Player* p ) override;

	void ChangeState( Player* p ) override;

	void Update( Player* p ) override;

private:
};

}

