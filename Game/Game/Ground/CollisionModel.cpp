#include "stdafx.h"
#include "CollisionModel.h"

CollisionModel::CollisionModel( const wchar_t* modelPath, const wchar_t* collisionModelPath ) {
	m_model.Init(modelPath);
	if( !collisionModelPath ){
		m_collider.CreateMeshObject( m_model.GetModel(), { 0,0,0 }, CQuaternion::Identity() );
	} else{
		m_collider.CreateMeshObject( collisionModelPath, { 0,0,0 }, CQuaternion::Identity() );
	}
}

CollisionModel::~CollisionModel() {
}

void CollisionModel::SetPos(const CVector3 & pos) {
	m_model.SetPos(pos);
	m_model.Update();
	m_collider.SetPos(pos);
}
