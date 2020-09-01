#pragma once
#include "Actor/Enemy/Act/EnemyAct.h"

namespace EnemySpace{

class Idle : public EnemyAct{
public:
	void SubStart( Actor* s ) override;
	void Update( Actor* s ) override;
};

}