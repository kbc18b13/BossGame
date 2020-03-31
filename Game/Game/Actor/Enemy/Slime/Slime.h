#pragma once
#include "Actor/Actor.h"
#include "Weapon/ArmWeapon.h"
#include "Util/MiniBarGauge.h"

namespace EnemySpace{
class EnemyAct;
}

class Slime : public Actor{
public:

	Slime( IStage* stage );
	~Slime();

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
		Walk,
		Strike,
		HeavyStrike,
		RollAttack,
		RollEnd,
		Avoid,
		Hit,
		Num
	};
	//ステート
	enum class ActE{
		Idle,
		Chase,
		Strike,
		Hit,
		Avoid,
		RollAttack,
		Num,
	};

private:
	Act* GetAct( int index ) override;

	//HPバー
	MiniBarGauge m_hpBar;

	//攻撃判定
	ArmWeapon m_weapon;

	//アニメーション
	AnimationClip m_animClip[int( Anim::Num )];

	//ステート
	std::unique_ptr<EnemySpace::EnemyAct> m_stateArray[int( ActE::Num )];

	//音
	SoundOverlap m_se_strike;
};

