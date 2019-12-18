#pragma once
#include "Act.h"
#include "graphics/CFont.h"
class Player;

namespace TrollAct{

class ActStep : public Act{
public:
	ActStep();

	void Start( Troll* t ) override;
	void Continue( Troll* t ) override;

private:
	bool first = true;
	bool onJump = false;

	CFont font;
};

}