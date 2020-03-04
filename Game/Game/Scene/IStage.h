#pragma once
#include <vector>
class Actor;
class Player;

class IStage : public IGameObject{
public:
	IStage();
	virtual ~IStage();

	Player* GetPlayer(){
		return player;
	}

	std::vector<Actor*>& GetEnemys(){
		return enemyArray;
	}

	virtual void EndStage() = 0;

protected:
	Player* player;
	std::vector<Actor*> enemyArray;
};

