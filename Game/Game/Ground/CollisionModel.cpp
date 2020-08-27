#include "stdafx.h"
#include "CollisionModel.h"
#include "Actor/Actor.h"
#include "physics/CollisionAttr.h"

CollisionModel::CollisionModel( const wchar_t* modelPath, const wchar_t* collisionModelPath,
								btCollisionObject::CollisionFlags flag, bool alpha ){
	m_model.Init( { modelPath, nullptr, 0, enFbxUpAxisY,true, alpha } );
	m_collider.SetFlag( flag );
	if( !collisionModelPath ){
		m_collider.CreateMeshObject( m_model.GetModel(), { 0,0,0 }, CQuaternion::Identity() );
	} else{
		m_collider.CreateMeshObject( collisionModelPath, { 0,0,0 }, CQuaternion::Identity() );
	}
}

CollisionModel::~CollisionModel(){}

void CollisionModel::SetPos( const CVector3 & pos ){
	m_model.SetPos( pos );
	m_model.Update();
	m_collider.SetPos( pos );
}

void CollisionModel::SetRot( const CQuaternion & rot ){
	m_model.SetRot( rot );
	m_model.Update();
	m_collider.SetRot( rot );
}

void CollisionModel::SetScale( const CVector3 & scale ){
	m_model.SetScale( scale );
	m_model.Update();
	m_collider.SetScale( scale );
}

class CharaContact : public btCollisionWorld::ContactResultCallback{
public:
	CharaContact(){}
	~CharaContact(){}

	btScalar	addSingleResult( btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap,
								 int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap,
								 int partId1, int index1 ){
		const btCollisionObject* co = colObj0Wrap->getCollisionObject();
		if( co->getUserIndex() == enCollisionAttr_Enemy || co->getUserIndex() == enCollisionAttr_Player ){
			Actor* a = static_cast<Actor*>( co->getUserPointer() );
			CVector3 rebound = -CVector3(cp.m_normalWorldOnB) * cp.getDistance();
			a->SetPos( a->GetPos() + rebound );
		}

		return 0.0f;
	}
};

void CollisionModel::CollideChara(){
	CharaContact cb;
	g_physics.ContactTest(m_collider.GetRigidBody()->GetBody(), cb);
}
