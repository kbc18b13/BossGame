#pragma once
#include "Act.h"
#include "graphics/CFont.h"

class Player;
class TrollBodyCollision;

namespace TrollAct{

class ActHip : public Act{
public:
	ActHip(TrollBodyCollision& col);

	void Start(Troll* t) override;
	void Continue( Troll* t );

private:
	bool first = true;
	bool onJump = false;
	float waitTime;

	TrollBodyCollision& bodyCol;
};

}