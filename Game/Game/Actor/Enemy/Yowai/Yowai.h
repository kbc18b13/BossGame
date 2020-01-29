#pragma once
#include "Actor/Actor.h"

class IStage;

namespace EnemySpace{
class EnemyAct;
}

class Yowai : public Actor{
public:
	Yowai(IStage* stage);
	~Yowai();

private:
	//�A�j���[�V����
	enum class Anim{
		Attack,
		Idle,
		Hit,
		Walk,
		Num
	};
	AnimationClip m_animClips[int(Anim::Num)];

	//�X�e�[�g
	std::unique_ptr<EnemySpace::EnemyAct> m_stateArray[int( Anim::Num )];
};

