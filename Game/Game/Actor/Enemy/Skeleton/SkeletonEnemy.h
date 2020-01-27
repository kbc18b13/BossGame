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

	bool Damage( UINT damage, Actor* source ) override{
		m_hpBar.view();
		return Actor::Damage( damage, source );
	}

	//�A�j���[�V�������X�e�[�g
	enum class Anim{
		Idle,
		Chase,
		Attack1,
		Attack2,
		Num,
	};
private:

	//�A�j���[�V����
	AnimationClip m_animClip [int( Anim::Num )];

	//��
	ModelArmWeapon m_sword;

	MiniBarGauge m_hpBar;

	//�X�e�[�g
	std::unique_ptr<SkeletonAct::Act> stateArray[int( Anim::Num )];
	SkeletonAct::Act* nowAct = nullptr;
	//�X�e�[�g�ύX�֐�
	void ChangeAct( Anim state );

	friend SkeletonAct::Act;
};

