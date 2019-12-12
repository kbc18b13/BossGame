#pragma once
#include "Util/ActorHitCollision.h"
#include "physics/BoxCollider.h"
#include "Damage/Attack.h"

class Troll;

class TrollArmCollision {
public:
    TrollArmCollision();
    ~TrollArmCollision();

    void Init(Troll* troll, Bone* arm);
    void Update();

    void StartAttack() {
        isAttack = true;
    }
    void EndAttack() {
        isAttack = false;
    }

private:
	UINT damage = 1;
	float coolTime = 3.0f;

    bool isAttack = false;

    Troll* m_master = nullptr;

    BoxCollider m_boxCol; //当たり判定の形
    Bone* m_hand; //手のボーン

    ActorHitCollision m_collision;
};

