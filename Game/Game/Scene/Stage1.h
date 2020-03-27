#include "Ground/CollisionModel.h"
#include "Ground/TriggerCollision.h"
#include "Ground/BigDoor.h"
#include "IStage.h"
#include "WayPoint/WayPointManager.h"

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

	virtual CVector3 GetShouldGo( const CVector3& from, const CVector3& to ){
		return wpManager.GetShouldGo( from, to );
	}

private:
	//�X�e�[�W�I���܂ł̎���
	float endTime = 0.0f;
	//�X�e�[�W�I���t���O
	bool isEndStage = false;


	TriggerCollision* bossRoomTrigger = nullptr;
	CVector3 trollPos;
	CollisionModel ground;
	CollisionModel carriage;
	DoorOpener opener;
	BigDoor* bigDoor = nullptr;

	//�E�F�C�|�C���g���Ǘ�
	WayPointManager wpManager;
};