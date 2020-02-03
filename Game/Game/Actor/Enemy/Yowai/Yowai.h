#pragma once
#include "Actor/Actor.h"
#include "Util/MiniBarGauge.h"
#include "Weapon/ArmWeapon.h"

class DoorOpener;

class IStage;

namespace EnemySpace{
class EnemyAct;
}

class Yowai : public Actor{
public:
	Yowai(IStage* stage);
	~Yowai();

	void Update() override;

	bool Damage( UINT damage, Actor* source ) override{
		m_hpBar.view();
		ChangeAct( int( Anim::Hit ) );
		return Actor::Damage( damage, source );
	}

	void SetOpener( DoorOpener* opener ){
		m_opener = opener;
	}

	//アニメーション
	enum class Anim{
		Attack,
		Idle,
		Hit,
		Walk,
		Num
	};
private:
	Act* GetAct( int index ) override;

	AnimationClip m_animClips[int(Anim::Num)];

	//ステート
	std::unique_ptr<EnemySpace::EnemyAct> m_stateArray[int( Anim::Num )];

	MiniBarGauge m_hpBar;

	ArmWeapon m_weapon;

	DoorOpener* m_opener = nullptr;
};

