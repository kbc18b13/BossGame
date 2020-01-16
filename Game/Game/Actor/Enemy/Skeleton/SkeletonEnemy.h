#pragma once
#include "Actor/Actor.h"
#include "graphics/SkinModelRender.h"
#include "Util/CharaConEx.h"

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

private:
	CharaConEx m_chara;

	enum class Anim{
		Idle,
		Walk,
		Attack1,
		Attack2,
		Num,
	};
	AnimationClip m_animClip [int( Anim::Num )];
	SkinModelRender m_model;
};

