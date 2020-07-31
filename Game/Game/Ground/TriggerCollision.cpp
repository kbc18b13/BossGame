#include "stdafx.h"
#include "TriggerCollision.h"
#include "physics/CollisionAttr.h"

struct TriggerResult : btCollisionWorld::ContactResultCallback{

	bool isHit = false;

	btScalar	addSingleResult( btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap,
								 int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap,
								 int partId1, int index1 ){
		const btCollisionObject* co = colObj1Wrap->getCollisionObject();
		if( co->getUserIndex() == enCollisionAttr_Player ){
			isHit = true;
		}
		return 0.0f;
	}

private:
	EnCollisionAttr target;
};

TriggerCollision::TriggerCollision(){}

TriggerCollision::~TriggerCollision(){
	g_physics.RemoveCollision(m_coll);
}

void TriggerCollision::Init( std::function<void()> func, const CVector3& halfExtents,
							 const CVector3& pos, const CQuaternion& rot ){
	m_boxShape.Create( halfExtents.toBT() );
	m_coll.Create( m_boxShape, pos, rot );
	m_coll.SetMask( 0 );
	m_func = func;
	g_physics.AddCollision( m_coll );
}

void TriggerCollision::Update(){
	TriggerResult result;
	g_physics.ContactTest( m_coll.GetBody(), result );
	if( result.isHit ){
		m_func();
	}
}
