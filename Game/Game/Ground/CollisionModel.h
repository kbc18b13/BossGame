#include "physics/PhysicsStaticObject.h"
class SkinModelRender;
class CollisionModel {
public:
	CollisionModel(const wchar_t* modelPath, const wchar_t* collisionModelPath = nullptr);
	~CollisionModel();

	void SetPos(const CVector3& pos);

	void SetRot( const CQuaternion& rot );

private:
	SkinModelRender m_model;
	PhysicsStaticObject m_collider;
};