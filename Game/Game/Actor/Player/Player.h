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

	/// <summary>
	/// �ʒu���擾
	/// </summary>
	CVector3 GetPos() {
		return m_charaCon.GetPosition();
	}

	/// <summary>
	/// �ʒu��ݒ�
	/// </summary>
	void SetPos(const CVector3& pos) {
		m_charaCon.SetPosition(pos);
	}

private:
	static constexpr float WALK_MAX = 200;
	static constexpr float WALK_ACCEL_AIR = 10;
	static constexpr float WALK_ACCEL = 50;
	static constexpr float WALK_BLAKE = 20;
	static constexpr float JUMP_POWER = 350;

	CVector3 m_walkSpeed;//�ړ����x
	float jumpSpeed = 0;
	CQuaternion rot;//��]

	enum EnAnim {
		enAnimWalk,
		enAnimSlash,
		enAnimNum
	};
	AnimationClip m_animClip[enAnimNum];        //�A�j���[�V�����N���b�v
	SkinModelRender* m_model;                    //�����̃��f���B
	SkinModel m_swordModel;                    //���̃��f���B

	CharacterController m_charaCon;             //�L�����R��

	PlayerCamera m_camera;                      //�J����
};

