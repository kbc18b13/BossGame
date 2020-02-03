#include "Ground/CollisionModel.h"
#include "Ground/TriggerCollision.h"
#include "Ground/BigDoor.h"
#include "IStage.h"
class Troll;
class Player;
class Stage1 : public IStage {
public:
	Stage1();
	~Stage1();
	void Update();

	void EndStage() override;

private:
	float endTime = 0.0f;
	bool isEndStage = false;
	CVector3 trollPos;
	CollisionModel ground;
	CollisionModel carriage;
	BigDoor* bigDoor = nullptr;
	TriggerCollision* bossRoomTrigger;
};