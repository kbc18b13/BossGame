#pragma once
#include "Act.h"

namespace PlayerAct{

class Attack : public Act{
public:
	Attack();
	~Attack();

	void ChangeState( ActArg& arg ) override;

	void Update( ActArg& arg ) override;

	void Init( Player::Anim animation_, Attack* nextAttack_ = nullptr ){
		animation = animation_;
		nextAttack = nextAttack_;
	}

private:
	Player::Anim animation;
	Attack* nextAttack;
	bool pushedAtkButton = false;
};

}