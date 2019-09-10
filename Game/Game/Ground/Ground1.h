#include "physics/PhysicsStaticObject.h"
class SkinModelRender;
class Ground {
public:
	Ground();
	~Ground();
private:
	SkinModelRender* m_model;
	PhysicsStaticObject m_collider;
};