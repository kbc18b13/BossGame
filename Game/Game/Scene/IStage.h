#pragma once
#include "graphics/SkinModelRender.h"
#include "StageManager.h"
#include <vector>
class Actor;
class Player;

class IStage : public IGameObject{
public:
	IStage(StageManager* manager);
	virtual ~IStage();

	Player* GetPlayer(){
		return manager->GetPlayer();
	}

	std::vector<Actor*>& GetEnemys(){
		return enemyArray;
	}

	virtual CVector3 GetShouldGo( const CVector3& from, const CVector3& to ){
		return to;
	}

	void EndStage(){
		manager->EndStage();
	}

	virtual void SetStageStencilRef(int ref) = 0;
protected:
	StageManager* manager = nullptr;
	std::vector<Actor*> enemyArray;
};

