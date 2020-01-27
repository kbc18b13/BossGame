#pragma once
#include "Act.h"

namespace PlayerAct{

class Attack : public Act{
public:
	Attack( Player::Anim animation_, Player::Anim nextAttack_);
	~Attack();

	void Start( Player* p ) override;

	void ChangeState( Player* p ) override;

	void Update( Player* p ) override;

	/*void Init( Player::Anim animation_, Act* nextAttack_ = nullptr ){
		animation = animation_;
		nextAttack = nextAttack_;
	}*/

private:
	Player::Anim animation;
	Player::Anim nextAttack;
	bool pushedAtkButton = false;
	float m_timer = 0;
};

}