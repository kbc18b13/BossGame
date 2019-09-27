#pragma once
#include "physics/BoxCollider.h"
#include "physics/CollisionObject.h"
class SkinModelRender;

class Sword : public IGameObject{
public:
	Sword(Bone* handBone);
	~Sword();
	void SetOffset(const CVector3& offset) {
		m_offset = offset;
	}
	void Update() override;

private:
	Bone* m_hand; //手のボーン

	btGhostObject m_col;
	SkinModelRender* m_model = nullptr;
	BoxCollider		 m_collider;				//コライダー。
	CollisionObject  m_collision;              //コリジョン。
	CVector3 m_offset; //位置オフセット
};