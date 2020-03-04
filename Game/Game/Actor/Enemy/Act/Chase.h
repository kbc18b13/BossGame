#pragma once
#include "EnemyAct.h"
class Player;

namespace EnemySpace{

class Chase : public EnemyAct{
public:
	Chase(int walkAnim, int nextState, float stopDistance);
	~Chase();

	void SubStart( Actor* a ) override;

	void Update( Actor* a ) override;

private:
	int m_nextState;
	int m_walkAnim;
	float m_stopDistance = 0.0f;
	float m_timer = 0.0f;
};

}