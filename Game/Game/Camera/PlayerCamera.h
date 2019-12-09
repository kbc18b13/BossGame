#pragma once
#include "graphics/SpriteRender.h"
#include "Actor/Actor.h"

class IStage;

class PlayerCamera {
public:
	PlayerCamera();

	/// <summary>
	/// �v���C���[���W��^���ăJ�����ʒu���X�V����
	/// </summary>
	/// <param name="playerPos">�v���C���[�̈ʒu</param>
	void Update(const CVector3& playerPos);

	/// <summary>
	/// �v���C���[����J�����ւ̃x�N�g����ݒ肷��B
	/// </summary>
	/// <param name="vec">�v���C���[����J�����ւ̃x�N�g��</param>
	void SetVec(CVector3 vec) {
		m_vec = vec;
		vec.Normalize();
		m_UpDownRot = CMath::RadToDeg(acosf(CVector3::AxisY().Dot(vec)));
	}

	void TurnLockOn(IStage* stage);

	/// <summary>
	/// �J�����̑O����
	/// </summary>
	/// <returns></returns>
	CVector3 GetFrontVec_XZ() {
		CVector3 front = -m_vec;
		front.y = 0;
		front.Normalize();
		return front;
	}

	/// <summary>
	/// �J�����̉E����
	/// </summary>
	/// <returns></returns>
	CVector3 GetRightVec() {
		CVector3 right = CVector3::AxisY();
		right.Cross(-m_vec);
		right.Normalize();
		return right;
	}

	/// <summary>
	/// ���b�N�I�����Ȃ�True
	/// </summary>
	bool IsLockOn(){
		return m_lockOnEnemy != nullptr;
	}

	/// <summary>
	/// ���b�N�I���Ώۂ̈ʒu���擾�B���b�N�I�����ȊO�̓G���[�B
	/// </summary>
	CVector3 GetLockOnPos(){
		return m_lockOnEnemy->GetPos();
	}

private:
	static constexpr float ROT_SPEED = 180;//�J������]�X�s�[�h�B�x/�b�B
	static constexpr float LIMIT_UP_DOWN_ROT = 80;//�㉺��]�̐����B�x�B0�x�`90�x�B
	static constexpr int TARGET_RANGE = 400; //�^�[�Q�b�g�\�ȋ���

	float m_UpDownRot = 0.0f; //�㉺�̉�]�B�x�B

	CVector3 m_vec = {0,0,-100};//�v���C���[����J�����ւ̃x�N�g��
	CVector3 m_pos;//�J�����̈ʒu

	Actor* m_lockOnEnemy = nullptr;

	SpriteRender m_lockOnSprite;
};