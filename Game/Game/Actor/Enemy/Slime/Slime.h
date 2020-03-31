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

	//�A�j���[�V����
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
	//�X�e�[�g
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

	//HP�o�[
	MiniBarGauge m_hpBar;

	//�U������
	ArmWeapon m_weapon;

	//�A�j���[�V����
	AnimationClip m_animClip[int( Anim::Num )];

	//�X�e�[�g
	std::unique_ptr<EnemySpace::EnemyAct> m_stateArray[int( ActE::Num )];

	//��
	SoundOverlap m_se_strike;
};

