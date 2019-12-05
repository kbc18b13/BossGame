#pragma once
#include <vector>;
#include "Actor/Actor.h"

class IStage : public IGameObject{
public:
	IStage();
	virtual ~IStage();

	std::vector<Actor*>& GetEnemys(){
		return enemyArray;
	}

protected:
	std::vector<Actor*> enemyArray;
};

