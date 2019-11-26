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

	Bone* m_hand; //手のボーン

	SkinModelRender m_model;
	BoxCollider		 m_collider;				//コライダー。
	CollisionObject  m_collision;              //コリジョン。
	CVector3 m_offset; //位置オフセット

	bool m_isSlash = false;  //攻撃中ならtrue
	Attack m_atk;
};