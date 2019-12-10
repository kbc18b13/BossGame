#pragma once
#include "Actor/Actor.h"
#include "Camera/PlayerCamera.h"
#include "Util/CharaConEx.h"
#include "Sword.h"
#include "Shield.h"
#include "Util/BarGauge.h"

class Sword;
class SkinModelRender;
namespace PlayerAct{
class Act;
}

class Player : public Actor
{
public:
	Player();
	~Player();

	void Update() override;

	/// <summary>
	/// �ʒu���擾
	/// </summary>
	CVector3 GetPos() const override{
		return m_charaCon.GetPosition();
	}

	/// <summary>
	/// �ʒu��ݒ�
	/// </summary>
	void SetPos(const CVector3& pos)  override {
		m_charaCon.SetPosition(pos);
	}

    /// <summary>
    /// ����������
    /// </summary>
    void AddVelocity(const CVector3& pos) override {
        m_charaCon.AddVelocity(pos);
    }

	//�X�e�[�W���Z�b�g
	void SetStage( IStage* stage ){
		m_stage = stage;
	}

	enum class Anim{
		Walk,
		Idle,
		Slash,
		Slash2,
		Slash3,
		Slash4,
		Guard,
		Num,
	};

private:
	void ChangeAnimation( Anim anim );
	void SlashEnd();

	PlayerAct::Act* actArray[3];
	PlayerAct::Act* nowAct;

	static constexpr float WALK_MAX = 200;
	static constexpr float WALK_ACCEL_AIR = 10;
	static constexpr float WALK_ACCEL = 50;
	static constexpr float WALK_BLAKE = 20;
	static constexpr float JUMP_POWER = 350;

	CQuaternion rot;//��]

	AnimationClip m_animClip[int(Anim::Num)];        //�A�j���[�V�����N���b�v
	SkinModelRender m_model;                    //�����̃��f���B

	Sword m_sword;
	Shield m_shield;

	CharaConEx m_charaCon;             //�L�����R��

	PlayerCamera m_camera;                      //�J����

	BarGauge m_hpBar;//HP�o�[

	IStage* m_stage;

	static constexpr int MAX_COMBO = 4;
	int m_comboCount = -1;
	bool m_comboContinue = false;
};

