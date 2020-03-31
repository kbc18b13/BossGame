#pragma once
#include "PlayerAct.h"

namespace PlayerSpace{

class Roll : public PlayerAct{
public:
	Roll();
	~Roll();

	void SubStart( Actor* p ) override;

	void Update( Actor* p ) override;

private:
	CVector3 m_move;
	SoundOverlap m_sound;
};

}

