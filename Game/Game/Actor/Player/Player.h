#pragma once
#include "character/CharacterController.h"
#include "graphics/SkinModelRender.h"
#include "character/CharacterController.h"

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

	CVector3 m_moveSpeed;

	AnimationClip m_animClip[enAnimNum];
	std::unique_ptr<SkinModelRender> m_model;	//�X�L�����f�������_�[�B
	CharacterController m_charaCon;             //�L�����R��
};

