#pragma once
#include "Actor/Enemy/Act/EnemyAct.h"

namespace EnemySpace{

class YowaAttack : public EnemyAct{
public:
	YowaAttack();
	virtual ~YowaAttack();

	void SubStart( Actor* s ) override;
	void Update( Actor* s ) override;

private:
};

}