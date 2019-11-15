#include "stdafx.h"
#include "TrollArmCollision.h"
#include "physics/CollisionAttr.h"
#include "Actor/Actor.h"

TrollArmCollision::TrollArmCollision() {
}


TrollArmCollision::~TrollArmCollision() {
}

void TrollArmCollision::Init(Troll* troll, Bone* arm) {
    m_boxCol.Create(btVector3(10.0f, 20.0f, 10.0f));
    m_collision.Init(m_boxCol, EnCollisionAttr::enCollisionAttr_Player, troll);
    m_collision.SetOffset(CVector3(0, 20, 0));
    m_hand = arm;
}

void TrollArmCollision::Update() {
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
    for (Actor* a : hits) {
        CVector3 pos = a->GetPos();
        pos.y += 40;
        a->SetPos(pos);
    }
}
