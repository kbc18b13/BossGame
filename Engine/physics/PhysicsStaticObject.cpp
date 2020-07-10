/*!
 * @brief	静的オブジェクト。
 */


#include "stdafx.h"
#include "physics/PhysicsStaticObject.h"


PhysicsStaticObject::PhysicsStaticObject()
{
}
PhysicsStaticObject::~PhysicsStaticObject()
{
	SetActive( false );
}

void PhysicsStaticObject::CreateRigidBody( CVector3 pos, CQuaternion rot ){
	//剛体を作成、
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider; //剛体に形状(コライダー)を設定する。
	rbInfo.mass = 0.0f;
	rbInfo.pos = pos;
	rbInfo.rot = rot;
	m_rigidBody.Create( rbInfo );
	m_rigidBody.GetBody()->setCollisionFlags( m_flag );
	//剛体を物理ワールドに追加する。
	g_physics.AddRigidBody( m_rigidBody );
}

void PhysicsStaticObject::SetActive( bool active ){
	if( m_isActive && !active ){
		g_physics.RemoveRigidBody( m_rigidBody );
	}
	if( !m_isActive && active ){
		g_physics.AddRigidBody( m_rigidBody );
	}
	m_isActive = active;
}
