#pragma once
#include "Act.h"
#include "graphics/CFont.h"
class Player;

namespace TrollAct{

class ActStep : public Act{
public:
	ActStep();

	void Start() override;
	void Continue( ActArg& arg );

private:
	bool first = true;
	bool onJump = false;

	CFont font;
};

}