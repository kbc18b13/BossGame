#pragma once
#include "Actor\Enemy\Act\EnemyAct.h"
#include "graphics/CFont.h"
class Player;

namespace EnemySpace{

class TrollStep : public EnemyAct{
public:
	TrollStep();

	void SubStart( Actor* t ) override;
	void Update( Actor* t ) override;

private:
	bool first = true;
	bool onJump = false;
};

}