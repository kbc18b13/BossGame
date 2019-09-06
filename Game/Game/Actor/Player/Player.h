#pragma once
#include "character/CharacterController.h"
#include "graphics/SkinModelRender.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Update() override;

private:
	enum EnAnim{
		enAnimWalk,
		//enAnimRun,
		enAnimNum
	};
	AnimationClip m_animClip[enAnimNum];
	std::unique_ptr<SkinModelRender> m_model;	//スキンモデルレンダー。
};

