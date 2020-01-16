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
	/// �J���������猩���p�b�h����
	/// </summary>
	/// <returns>���[���h���W�n�̃x�N�g��</returns>
	CVector3 GetPadVec();

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
	static constexpr float CtoPLength = 100;

	float m_upDownRot = 0.0f; //�㉺�̉�]�B�x�B

	CVector3 m_vec = {0,0,-100};//�v���C���[����J�����ւ̃x�N�g��
	CVector3 m_pos;//�J�����̈ʒu

	CVector3 m_oldPlayerPos;

	Actor* m_lockOnEnemy = nullptr;

	SpriteRender m_lockOnSprite;
};