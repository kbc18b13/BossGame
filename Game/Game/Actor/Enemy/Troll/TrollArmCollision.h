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
        m_attack.UpdateAttackID();
        isAttack = true;
    }
    void EndAttack() {
        isAttack = false;
    }

private:
    bool isAttack = false;
    Attack m_attack;
    Troll* m_master = nullptr;
    BoxCollider m_boxCol; //ìñÇΩÇËîªíËÇÃå`
    Bone* m_hand; //éËÇÃÉ{Å[Éì
    ActorHitCollision m_collision;
};

