#include "stdafx.h"
#include "GhostCollision.h"

GhostCollision::GhostCollision(){}

GhostCollision::~GhostCollision(){
	g_physics.RemoveCollision( m_collision );
}

void GhostCollision::Init( const wchar_t * filepath, short mask, const CVector3& pos, const CQuaternion& rot ){
	m_collider.CreateFromCMOFile( filepath );
	m_collision.SetGroup( btCollisionObject::CF_Ground );
	m_collision.SetMask( mask );
	m_collision.Create( m_collider, pos, rot );
	g_physics.AddCollision( m_collision );
}
