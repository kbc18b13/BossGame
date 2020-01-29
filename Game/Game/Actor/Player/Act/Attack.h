#pragma once
#include "PlayerAct.h"

namespace PlayerSpace{

class Attack : public PlayerAct{
public:
	Attack( Player::Anim animation1, int combo);
	~Attack();

	void SubStart( Actor* p ) override;

	void Update( Actor* p ) override;

	void End( Actor * p ) override;

private:
	int m_animation;
	const int m_maxCombo;
	bool m_pushedAtkButton = false;
	int m_nowCombo = 1;
	float m_timer = 0;
};

}