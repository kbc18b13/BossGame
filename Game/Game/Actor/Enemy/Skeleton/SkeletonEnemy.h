#pragma once
#include "Actor/Actor.h"
#include "graphics/SkinModelRender.h"
#include "Util/CharaConEx.h"
#include "Weapon/ModelArmWeapon.h"
#include "Util/MiniBarGauge.h"

namespace SkeletonAct{
class Act;
}

class SkeletonEnemy : public Actor{
public:
	SkeletonEnemy( IStage* stage );
	~SkeletonEnemy();

	void Update() override;

	void SetPos( const CVector3& pos ) override{
		m_chara.SetPosition( pos );
		m_model.SetPos( pos );
	}
	CVector3 GetPos() const override{
		return m_chara.GetPosition();
	}
	void AddVelocity( const CVector3& v ) override{
		m_chara.AddVelocity( v );
	}

	bool Damage( UINT damage, Actor* source ) override{
		m_hpBar.view();
		return Actor::Damage( damage, source );
	}

	//アニメーション兼ステート
	enum class Anim{
		Idle,
		Chase,
		Attack1,
		Attack2,
		Num,
	};
private:
	//キャラコン
	CharaConEx m_chara;

	//アニメーションとモデル
	AnimationClip m_animClip [int( Anim::Num )];
	SkinModelRender m_model;

	//剣
	ModelArmWeapon m_sword;

	MiniBarGauge m_hpBar;

	//ステート
	std::unique_ptr<SkeletonAct::Act> stateArray[int( Anim::Num )];
	SkeletonAct::Act* nowAct = nullptr;
	//ステート変更関数
	void ChangeAct( Anim state );

	friend SkeletonAct::Act;
};

