#pragma once
#include "Act.h"
#include "graphics/CFont.h"
class Player;

namespace TrollAct{

class ActTackle : public Act{
public:
	ActTackle();

	void Start() override;
	void Continue( ActArg& arg );

private:
	float m_timer = 0.0f;
};

}