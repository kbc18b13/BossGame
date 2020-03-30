#pragma once
#include "physics/MeshCollider.h"
#include "physics/CollisionObject.h"

class GhostCollision{
public:
	GhostCollision();
	~GhostCollision();

	void Init( const wchar_t* filepath , const CVector3& pos = CVector3::Zero(),
			   const CQuaternion& rot = CQuaternion::Identity());

private:
	CollisionObject m_collision;
	MeshCollider m_collider;
};

