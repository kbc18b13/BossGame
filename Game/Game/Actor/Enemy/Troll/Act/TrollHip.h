#pragma once
#include "Actor\Enemy\Act\EnemyAct.h"

class Player;
class TrollBodyCollision;

namespace EnemySpace{

class TrollHip : public EnemyAct{
public:
	TrollHip(TrollBodyCollision& col);

	void SubStart(Actor* t) override;
	void Update( Actor* t ) override;

private:
	bool first = true;
	bool onJump = false;
	float waitTime;

	TrollBodyCollision& bodyCol;
};

}