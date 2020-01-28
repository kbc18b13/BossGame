#pragma once
#include "PlayerAct.h"

namespace PlayerSpace{

class Attack : public PlayerAct{
public:
	Attack( Player::Anim animation_, Player::Anim nextAttack_);
	~Attack();

	void SubStart( Actor* p ) override;

	void Update( Actor* p ) override;

private:
	Player::Anim animation;
	Player::Anim nextAttack;
	bool pushedAtkButton = false;
	float m_timer = 0;
};

}