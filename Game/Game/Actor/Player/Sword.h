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
	Bone* m_hand; //��̃{�[��

	btGhostObject m_col;
	SkinModelRender* m_model = nullptr;
	BoxCollider		 m_collider;				//�R���C�_�[�B
	CollisionObject  m_collision;              //�R���W�����B
	CVector3 m_offset; //�ʒu�I�t�Z�b�g
};