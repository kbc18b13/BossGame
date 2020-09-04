#pragma once
#include "physics/CollisionAttr.h"

class Actor;

struct ActorHitResult{
	std::vector<Actor*> actors;
	bool groundHit = false;
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

	CMatrix GetWorldMatrix(){
		CMatrix mat;
		m_collision.GetBody()->getWorldTransform().getOpenGLMatrix( &mat._11 );
		return mat;
	}

    ActorHitResult ContactTest();

	void SetActive( bool active );

private:
    CollisionObject  m_collision;              //コリジョン。
    CVector3 m_pos; //位置
    CVector3 m_offset; //オフセット
    CQuaternion m_rot; //回転

	EnCollisionAttr m_targetIndex;

	bool m_isActive = true;
};

