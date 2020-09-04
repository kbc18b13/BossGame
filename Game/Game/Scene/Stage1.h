#include "Ground/CollisionModel.h"
#include "Ground/TriggerCollision.h"
#include "Ground/BigDoor.h"
#include "Ground/GhostCollision.h"
#include "IStage.h"
#include "WayPoint/WayPointManager.h"
#include "Ground/ClearDoor.h"
#include "Ground/SkyBox.h"

class Troll;
class Player;
class StageGate;

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
	Stage1( StageManager* manager );

	void Destroy() override;

	void Update() override;

	CVector3 GetShouldGo( const CVector3& from, const CVector3& to ) override{
		return wpManager.GetShouldGo( from, to );
	}

	void SetStageStencilRef( int ref ) override;

	CVector3 GetPlayerSpawn() const{
		return m_playerSpawn;
	}

private:
	TriggerCollision* bossRoomTrigger = nullptr;
	CVector3 trollPos;
	CollisionModel ground;
	ClearDoor bossTobira;
	CollisionModel carriage;
	DoorOpener opener;
	SkyBox sky;


	BigDoor* bigDoor = nullptr;

	GhostCollision m_wall;

	//ウェイポイントを管理
	WayPointManager wpManager;

	//BGM
	CSoundSource m_bgm;
	CSoundSource m_bossBGM;

	CVector3 m_playerSpawn;
};