#pragma once
#include "Act.h"
#include "graphics/CFont.h"
class Player;

namespace TrollAct{

class ActHip : public Act{
public:
	ActHip();

	void Start(Troll* t) override;
	void Continue( Troll* t );

private:
	bool first = true;
	bool onJump = false;
};

}