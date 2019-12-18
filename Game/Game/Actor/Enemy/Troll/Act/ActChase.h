#pragma once
#include "Act.h"

class Player;

namespace TrollAct{

class ActChase : public Act{
public:
	ActChase();

	void Start(Troll* t) override;
	void Continue( Troll* t );

private:
	float m_timer = 0.0f;
};

}