#pragma once
#include "physics/BoxCollider.h"
#include "physics/CollisionObject.h"

class TriggerCollision : public IGameObject{
public:
	TriggerCollision();
	~TriggerCollision();

	void Init(std::function<void()> func,const CVector3& halfExtents,const CVector3& pos,
			  const CQuaternion& rot = CQuaternion::Identity() );

	void Update() override;

private:
	BoxCollider m_boxShape;
	CollisionObject m_coll;
	std::function<void()> m_func;
};

