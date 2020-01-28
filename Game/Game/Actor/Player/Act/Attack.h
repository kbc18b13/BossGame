#pragma once
#include "Act.h"

namespace PlayerAct{

class Attack : public PlayerAct{
public:
	Attack( Player::Anim animation_, Player::Anim nextAttack_);
	~Attack();

	void SubStart( Actor* p ) override;

	void Update( Actor* p ) override;

	void End( Actor* p ) override;

private:
	Player::Anim animation;
	Player::Anim nextAttack;
	bool pushedAtkButton = false;
	float m_timer = 0;
};

}