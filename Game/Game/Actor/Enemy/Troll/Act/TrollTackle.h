#pragma once
#include "Actor\Enemy\Act\EnemyAct.h"
#include "graphics/CFont.h"
class Player;
class TrollBodyCollision;

namespace EnemySpace{

class TrollTackle : public EnemyAct{
public:
	TrollTackle(TrollBodyCollision& body);

	void SubStart( Actor* t ) override;
	void Update( Actor* t ) override;

private:
	CVector3 playerPos;
	float m_timer = 0.0f;
	TrollBodyCollision& bodyCol;
};

}