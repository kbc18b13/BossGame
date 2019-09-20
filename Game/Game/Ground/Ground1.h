#include "physics/PhysicsStaticObject.h"
class SkinModelRender;
class Ground {
public:
	Ground();
	~Ground();

	void SetPos(const CVector3& pos);

private:
	SkinModelRender* m_model;
	PhysicsStaticObject m_collider;
};