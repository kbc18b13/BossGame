#pragma once
#include "Act.h"
#include "graphics/CFont.h"
class Player;

namespace TrollAct{

class ActHip : public Act{
public:
	ActHip();

	void Start() override;
	void Continue( ActArg& arg );

private:
	bool first = true;
	bool onJump = false;
};

}