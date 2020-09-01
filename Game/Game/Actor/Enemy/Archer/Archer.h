#pragma once
#include "Actor\Actor.h"
#include "Util/MiniBarGauge.h"

namespace EnemySpace{
class EnemyAct;
}

namespace EnemySpace{

class Archer : public Actor{
public:
	Archer( IStage* stage );
	~Archer();

	void Update() override;

	void OnDeath() override;

	bool Damage( UINT damage, Actor* source ) override{
		m_hpBar.view();
		//ChangeAct( int( ActE::Hit ) );
		return Actor::Damage( damage, source );
	}

	void SetStencilRef( int ref ) override{
		m_model.GetModel().SetStencilRef( ref );
	}

	//アニメーション
	enum class Anim{
		Idle,
		Shot,
		Num,
	};
	//ステート
	enum class ActE{
		Idle,
		Shot,
		Num,
	};
private:
	Act* GetAct( int index ) override;

	//アニメーション
	AnimationClip m_animClip[int( Anim::Num )];

	MiniBarGauge m_hpBar;

	//ステート
	std::unique_ptr<EnemySpace::EnemyAct> m_stateArray[int( ActE::Num )];
};

}

