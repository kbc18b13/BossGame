#pragma once
#include "Util/ActorHitCollision.h"
#include "physics/BoxCollider.h"

class Troll;

class TrollArmCollision {
public:
    TrollArmCollision();
    ~TrollArmCollision();

    void Init(Troll* troll, Bone* arm);
    void Update();

private:
    BoxCollider m_boxCol; //�����蔻��̌`
    Bone* m_hand; //��̃{�[��
    ActorHitCollision m_collision;
};

