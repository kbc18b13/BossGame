#pragma once
#include "Actor/Actor.h"
#include "Util/CharaConEx.h"
#include "TrollBodyCollision.h"
#include "Util/BarGauge.h"
#include "graphics/FontRender.h"
#include "Weapon/ArmWeapon.h"

namespace EnemySpace{
class EnemyAct;
}

class Troll : public Actor{
public:
	//関数
	Troll( IStage* stage );
	~Troll();

	void Start() override;
	void Update() override;
	void OnDeath() override;

	void SetDeathFunc( std::function<void()> func ){
		m_deathFunc = func;
	}

	//列挙
	enum class AnimState{
		Walk,
		Attack,
		JumpUp,
		JumpDown,
		Idle,
		Tackle,
		Hip,
		Num
	};

	enum class ActState{
		Wait,
		Chase,
		Attack,
		Step,
		Tackle,
		Hip,
		Num,
	};

private:
	Act* GetAct( int index ) override;

	//現在のステート
	EnemySpace::EnemyAct* m_activeAction;
	//ステート配列
	std::unique_ptr<EnemySpace::EnemyAct> m_actionArray[int( ActState::Num )];

	AnimationClip m_animClip[int( AnimState::Num )];//アニメーションクリップ

	ArmWeapon m_armCollision;//腕の攻撃判定
	TrollBodyCollision m_bodyCollision;//体の攻撃判定

	BarGauge m_hpBar; //HPバー
	FontRender m_nameFont;

	std::function<void()> m_deathFunc;
};