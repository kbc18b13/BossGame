#pragma once
#include "Actor/Actor.h"
#include "graphics/SkinModelRender.h"
#include "Util/CharaConEx.h"
#include "Weapon/ModelArmWeapon.h"
#include "Util/MiniBarGauge.h"

namespace EnemySpace{
class EnemyAct;
}

class SkeletonEnemy : public Actor{
public:
	SkeletonEnemy( IStage* stage );
	~SkeletonEnemy();

	void Update() override;

	void OnDeath() override;

	bool Damage( UINT damage, Actor* source ) override{
		m_hpBar.view();
		ChangeAct( int( ActE::Hit ) );
		return Actor::Damage( damage, source );
	}

	//アニメーション
	enum class Anim{
		Idle,
		Chase,
		Attack1,
		Attack2,
		SideWalk,
		Hit,
		JumpAttack,
		Num,
	};
	//ステート
	enum class ActE{
		Idle,
		Chase,
		Attack,
		SideWalk,
		Hit,
		JumpAttack,
		Num,
	};
private:
	Act* GetAct( int index ) override;

	//アニメーション
	AnimationClip m_animClip [int( Anim::Num )];

	//剣
	ModelArmWeapon m_sword;

	MiniBarGauge m_hpBar;

	//音
	SoundOverlap m_se_swordSwing;
	SoundOverlap m_se_swordSlash;

	//ステート
	std::unique_ptr<EnemySpace::EnemyAct> m_stateArray[int( ActE::Num )];
};

