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

class ActorHitCollision {
public:
    ActorHitCollision();
    ~ActorHitCollision();

    void Init(ICollider& collider, EnCollisionAttr target ,void* userPointer);

    void SetPos(CVector3 pos){
        m_pos = pos;
    }

    void SetRot(CQuaternion rot) {
        m_rot = rot;
    }

    void SetOffset(CVector3 offset) {
        m_offset = offset;
    }

    std::vector<Actor*>& ContactTest();

private:
    ActorContactResult contactCB;
    CollisionObject  m_collision;              //コリジョン。
    CVector3 m_pos; //位置
    CVector3 m_offset; //オフセット
    CQuaternion m_rot; //回転
};

