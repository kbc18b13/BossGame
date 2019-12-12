#include "stdafx.h"
#include "TrollArmCollision.h"
#include "physics/CollisionAttr.h"
#include "Actor/Actor.h"
#include "Actor/Enemy/Troll/Troll.h"

TrollArmCollision::TrollArmCollision(){
}


TrollArmCollision::~TrollArmCollision() {
}

void TrollArmCollision::Init(Troll* troll, Bone* arm) {
    m_boxCol.Create(btVector3(10.0f, 20.0f, 10.0f));
    m_collision.Init(m_boxCol, EnCollisionAttr::enCollisionAttr_Player, troll);
    m_collision.SetOffset(CVector3(0, 0, 0));
    m_hand = arm;
    m_master = troll;
}

void TrollArmCollision::Update() {
    if (!isAttack) {
        return;
    }

    //位置更新
    {
        const CMatrix& worldMat = m_hand->GetWorldMatrix();

        CQuaternion rot;
        rot.SetRotation(worldMat);
        m_collision.SetRot(rot);
        m_collision.SetPos(CVector3(worldMat.v[3]));
    }

    //接触テスト
    std::vector<Actor*> hits = m_collision.ContactTest();
    CVector3 pos = m_master->GetPos();
    for (Actor* a : hits) {
        if (a->Damage(damage , coolTime, m_master)) {
            CVector3 v = a->GetPos() - pos;
            v.Normalize();
            v.y += 2;
            v *= 100;
            a->AddVelocity(v);
        }
    }
}