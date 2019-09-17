#pragma once
#include "Camera/PlayerCamera.h"
#include "character/CharacterController.h"
#include "Util/ResistVector3.h"

class SkinModelRender;

class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Update() override;

	CVector3 GetPos() {
		return m_charaCon.GetPosition();
	}

private:
	static constexpr float WALK_SPEED = 20;
	static constexpr float WALK_SPEED_AIR = 2;
	static constexpr float JUMP_SPEED = 10;

	ResistVector3 m_moveSpeed;//�ړ����x
	CQuaternion rot;//��]

	enum EnAnim {
		enAnimWalk,
		//enAnimRun,
		enAnimNum
	};
	AnimationClip m_animClip[enAnimNum];        //�A�j���[�V�����N���b�v
	std::unique_ptr<SkinModelRender> m_model;	//�X�L�����f�������_�[�B

	CharacterController m_charaCon;             //�L�����R��

	PlayerCamera m_camera;                      //�J����
};

