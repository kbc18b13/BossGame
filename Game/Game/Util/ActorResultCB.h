#pragma once
#include "physics/CollisionAttr.h"

class Actor;

class ActorContactResult : public btCollisionWorld::ContactResultCallback {
public:
    ActorContactResult();
    ~ActorContactResult();

    void setTarget(int targetFlag) {
        target = targetFlag;
    }

    std::vector<Actor*>& getHits() {
        return hits;
    }

    void eraseHits() {
        hits.clear();
    }

    btScalar	addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap,
                                int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap,
                                int partId1, int index1);
private:
    std::vector<Actor*> hits;
    int target;
};

#include "physics/ICollider.h"
#include "physics/CollisionObject.h"

class ActorCollision {
public:
    ActorCollision();
    ~ActorCollision();

    void Init(ICollider& collider, void* userPointer);

    std::vector<Actor*>& ContactTest();

private:
    ActorContactResult contactCB;
    CollisionObject  m_collision;              //コリジョン。
    CVector3 m_offset; //位置オフセット
};

