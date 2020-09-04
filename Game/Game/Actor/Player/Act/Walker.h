#pragma once
#include "PlayerAct.h"

namespace PlayerSpace{

class Walker : public PlayerAct{
public:
	Walker(LongPressButton* dash);
	~Walker();

	void Update( Actor* p ) override;
private:
	LongPressButton* m_dash;
};

}