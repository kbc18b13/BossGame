#pragma once
#include "Act.h"
#include "graphics/CFont.h"
class Player;

namespace TrollAct{

class ActTackle : public Act{
public:
	ActTackle();

	void Start( Troll* t ) override;
	void Continue( Troll* t ) override;

private:
	float m_timer = 0.0f;
};

}