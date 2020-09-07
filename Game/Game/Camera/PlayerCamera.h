#pragma once
#include "graphics/SpriteRender.h"
#include "Actor/Actor.h"

class IStage;

class PlayerCamera {
public:
	PlayerCamera();

	void Init(Actor* player){
		m_player = player;
		CVector3 playerPos = m_player->GetPos();
		playerPos.y += m_player->GetHeight();
		m_springPPos = playerPos;
		m_pos = playerPos + m_vec;
	}

	/// <summary>
	/// �v���C���[���W��^���ăJ�����ʒu���X�V����
	/// </summary>
	/// <param name="playerPos">�v���C���[�̈ʒu</param>
	void Update();

	/// <summary>
	/// ���b�N�I����Ԃ�؂�ւ���B
	/// </summary>
	void TurnLockOn(){
		if( IsLockOn() ){
			UnLockOn();
			return;
		}
		LockOn();
	}

	/// <summary>
	/// ���b�N�I�����O���A�ă��b�N�I���������B
	/// </summary>
	void ReLockOn(){
		UnLockOn();
		LockOn( CVector2::Zero(), TARGET_RANGE / 2);
	}

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
		right = right.Cross(-m_vec);
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
	void LockOn(CVector2 pad = CVector2::Zero(), float targetLength = TARGET_RANGE );
	void UnLockOn(){
		m_lockOnEnemy->UnLockOn();
		m_lockOnEnemy = nullptr;
		m_lockOnSprite.SetIsDraw( false );
	}
	void UpdateGCamera( const CVector3& pos, const CVector3& look );

	static constexpr float ROT_SPEED = 180;//�J������]�X�s�[�h�B�x/�b�B
	static constexpr float LIMIT_UP_DOWN_ROT = 70;//�㉺��]�̐����B�x�B0�x�`90�x�B
	static constexpr int TARGET_RANGE = 800; //�^�[�Q�b�g�\�ȋ���
	static constexpr float CtoPLength = 70; //�v���C���[����J�����ւ̃x�N�g���̒���

	Actor* m_player = nullptr;
	CVector3 m_springPPos; //�v���C���[�ɒx��Ă��Ă����|�W�V����

	CVector3 m_vec = {0,0,-CtoPLength };//�v���C���[����J�����ւ̃x�N�g��
	CVector3 m_springVec = { 0,0,-CtoPLength }; //�J������]�ɒx��Ă��Ă����x�N�g��
	CVector3 m_pos;//�J�����̈ʒu

	Actor* m_lockOnEnemy = nullptr;

	SpriteRender m_lockOnSprite;
};