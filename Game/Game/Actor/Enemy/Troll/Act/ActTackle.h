#pragma once
#include "Act.h"
#include "graphics/CFont.h"
class Player;
class TrollBodyCollision;

namespace TrollAct{

class ActTackle : public Act{
public:
	ActTackle(TrollBodyCollision& body);

	void Start( Troll* t ) override;
	void Continue( Troll* t ) override;

private:
	CVector3 playerPos;
	float m_timer = 0.0f;
	TrollBodyCollision& bodyCol;
};

}