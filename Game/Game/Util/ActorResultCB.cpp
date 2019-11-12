#include "stdafx.h"
#include "ActorResultCB.h"

ActorContactResult::ActorContactResult(){
}

ActorContactResult::~ActorContactResult() {
}

btScalar	ActorContactResult::addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap,
                            int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap,
                            int partId1, int index1) {
    //敵のコリジョンに当たった時、その敵のポインタを記憶する。
    const btCollisionObject* co = colObj1Wrap->getCollisionObject();
    if (co->getUserIndex() == target) {
        Actor* hited = static_cast<Actor*>(co->getUserPointer());
        hits.push_back(hited);
    }
    return 0.0f;
}

ActorCollision::ActorCollision() {
}

ActorCollision::~ActorCollision() {
}

void ActorCollision::Init(ICollider & collider, void* userPointer) {
    m_collision.Create(collider);
    m_collision.SetGroup(CollisionFlag::Ghost);
    m_collision.SetMask(CollisionFlag::);
    m_collision.SetUserPointer(userPointer);
    g_physics.AddCollision(m_collision);
}

std::vector<Actor*>& ActorCollision::ContactTest() {
    contactCB.eraseHits();
    g_physics.ContactText(m_collision.GetBody(), contactCB);
    return contactCB.getHits();
}
