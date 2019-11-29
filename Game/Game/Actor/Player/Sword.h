#pragma once
#include "physics/BoxCollider.h"
#include "physics/CollisionObject.h"
#include "Damage/DamageManager.h"
class SkinModelRender;
class Player;

class Sword : public IGameObject{
public:
	Sword(/*Bone* handBone, Player* p*/);
	~Sword();

    void Init(Bone* handBone, Player* p);

	void SetOffset(const CVector3& offset) {
		m_offset = offset;
	}
	void Update() override;

	void SlashStart();
	void SlashEnd();

private:

	Bone* m_hand; //��̃{�[��

	SkinModelRender m_model;
	BoxCollider		 m_collider;				//�R���C�_�[�B
	CollisionObject  m_collision;              //�R���W�����B
	CVector3 m_offset; //�ʒu�I�t�Z�b�g

	bool m_isSlash = false;  //�U�����Ȃ�true
	Attack m_atk;
};