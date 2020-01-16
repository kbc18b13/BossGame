#pragma once
#include "physics/BoxCollider.h"
#include "physics/CollisionObject.h"
#include "Damage/DamageManager.h"
class SkinModelRender;
class Actor;

class Sword{
public:
	Sword();
	~Sword();

    void Init(Bone* handBone, Actor* master, const CVector3& halfExtents , const wchar_t* modelpath);

	void SetOffset(const CVector3& offset) {
		m_offset = offset;
	}
	void Update();

	void SlashStart();
	void SlashEnd();

	void SetDamage(UINT damage){
		m_damage = damage;
	}

	void SetActive( bool active );

private:

	Bone* m_hand; //手のボーン

	Actor* m_master;

	SkinModelRender m_model;
	BoxCollider		 m_collider;				//コライダー。
	CollisionObject  m_collision;              //コリジョン。
	CVector3 m_offset; //位置オフセット

	bool m_isSlash = false;  //攻撃中ならtrue
	UINT m_damage = 1;
	float coolTime = 0.5f;

	bool m_isActive = true;
};