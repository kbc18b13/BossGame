/*!
 * @brief	�ÓI�I�u�W�F�N�g�B
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
	//���̂��쐬�A
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider; //���̂Ɍ`��(�R���C�_�[)��ݒ肷��B
	rbInfo.mass = 0.0f;
	rbInfo.pos = pos;
	rbInfo.rot = rot;
	m_rigidBody.Create( rbInfo );
	m_rigidBody.GetBody()->setCollisionFlags( m_flag );
	//���̂𕨗����[���h�ɒǉ�����B
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
