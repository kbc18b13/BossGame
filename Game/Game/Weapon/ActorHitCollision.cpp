#include "stdafx.h"
#include "ActorHitCollision.h"

class AHCCallback : public btCollisionWorld::ContactResultCallback{
public:
	AHCCallback(){
		m_collisionFilterGroup = btCollisionObject::CF_NO_CONTACT_RESPONSE;
	}
	~AHCCallback(){}

	void setTarget( int targetFlag ){
		target = targetFlag;
	}

	const ActorHitResult& getResult(){
		return result;
	}

	btScalar addSingleResult( btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap,
								int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap,
								int partId1, int index1 ){
		//敵のコリジョンに当たった時、その敵のポインタを記憶する。
		const btCollisionObject* co = colObj1Wrap->getCollisionObject();
		if( co->getUserIndex() == target ){
			Actor* hited = static_cast<Actor*>( co->getUserPointer() );
			result.actors.push_back( hited );
		}
		if( co->getCollisionFlags() == btCollisionObject::CF_Ground ){
			result.groundHit = true;
		}
		return 0.0f;
	}

private:
	ActorHitResult result;
	int target;
};

ActorHitCollision::ActorHitCollision() {
}

ActorHitCollision::~ActorHitCollision() {
    g_physics.RemoveCollision(m_collision);
}

void ActorHitCollision::Init(ICollider & collider, EnCollisionAttr target, void* userPointer) {
    m_collision.Create(collider);
    m_collision.SetGroup(btCollisionObject::CF_NO_CONTACT_RESPONSE);
    m_collision.SetMask(0);
    m_collision.SetUserIndex(enCollisionAttr_Ghost);
    m_collision.SetUserPointer(userPointer);
    g_physics.AddCollision(m_collision);
	m_targetIndex = target;
}

ActorHitResult ActorHitCollision::ContactTest() {
    //位置更新
    {
        m_collision.GetBody()->getWorldTransform().setRotation(m_rot.toBT() );

        CVector3 offset = m_offset;
        m_rot.Multiply(offset);
        CVector3 position = m_pos + offset;
        m_collision.GetBody()->getWorldTransform().setOrigin(position.toBT() );
    }

    //判定
	AHCCallback contactCB;
	contactCB.setTarget( m_targetIndex );
    g_physics.ContactTest(m_collision.GetBody(), contactCB);
	return contactCB.getResult();
}

void ActorHitCollision::SetActive( bool active ){
	if( m_isActive && !active){
		g_physics.RemoveCollision( m_collision );
	}
	if( !m_isActive && active ){
		g_physics.AddCollision( m_collision );
	}
	m_isActive = active;
}
