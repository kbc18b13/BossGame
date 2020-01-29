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
	//アニメーション
	enum class Anim{
		Attack,
		Idle,
		Hit,
		Walk,
		Num
	};
	AnimationClip m_animClips[int(Anim::Num)];

	//ステート
	std::unique_ptr<EnemySpace::EnemyAct> m_stateArray[int( Anim::Num )];
};

