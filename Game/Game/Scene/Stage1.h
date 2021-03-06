#include "Ground/CollisionModel.h"
#include "Ground/TriggerCollision.h"
#include "Ground/BigDoor.h"
#include "IStage.h"
class Troll;
class Player;

class DoorOpener{
public:
	void SetDoor( BigDoor* door_ ){
		door = door_;
	}

	void AddEnemyCount(){
		enemyCount++;
	}

	void DeathEnemy(){
		enemyCount--;
		if( enemyCount <= 0 ){
			door->Open();
		}
	}

private:
	BigDoor* door;
	int enemyCount = 0;
};

class Stage1 : public IStage {
public:
	Stage1();
	~Stage1();
	void Update();

	void EndStage() override;

private:
	//ステージ終了までの時間
	float endTime = 0.0f;
	//ステージ終了フラグ
	bool isEndStage = false;


	TriggerCollision* bossRoomTrigger = nullptr;
	CVector3 trollPos;
	CollisionModel ground;
	CollisionModel carriage;
	DoorOpener opener;
	BigDoor* bigDoor = nullptr;
};