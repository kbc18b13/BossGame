#pragma once
#include "Actor/Actor.h"
#include "Camera/PlayerCamera.h"
#include "Util/CharaConEx.h"
#include "Weapon/ModelArmWeapon.h"
#include "Shield.h"
#include "Util/BarGauge.h"
#include "Stamina.h"
#include "graphics/FontRender.h"

class SkinModelRender;

namespace PlayerSpace{
class PlayerAct;
}

class Player : public Actor
{
public:
	Player(IStage* stage);
	~Player();

	void Start() override;
	void Update() override;
	void OnDeath() override;
	/// <summary>
	/// �_���[�W��^����
	/// </summary>
	/// <param name="damage">�_���[�W</param>
	/// <param name="coolTime">�q�b�g��N�[���^�C��</param>
	/// <returns>�N�[���^�C������ɂ��_���[�W�̉�</returns>
	bool Damage( UINT damage, Actor* source ) override;

	enum class Anim{
		Walk,
		Idle,
		Slash1,
		Slash2,
		HeavySlash,
		Guard,
		Roll,
		Damage,
		Num,
	};

	enum class Act{
		Walker,
		Slash,
		Guard,
		Roll,
		Damage,
		Num,
		SlashEnd, //�U���I���̂��߂̃_�~�[
	};

private:
	::Act* GetAct( int index ) override;
	/// <summary>
	/// �f�t�H���g�̃X�e�[�g�ύX
	/// </summary>
	//void ChangeActDefault();

	/// <summary>
	/// �X�e�[�g�ύX
	/// </summary>
	/// <returns>�ύX�ɐ����������ǂ����B�X�^�~�i������Ȃ��Ǝ��s����B</returns>
	//bool ChangeAct( Anim act );

	std::unique_ptr<PlayerSpace::PlayerAct> m_actArray[int(Act::Num)];

	static constexpr float WALK_MAX = 200;
	static constexpr float WALK_ACCEL_AIR = 10;
	static constexpr float WALK_ACCEL = 50;
	static constexpr float WALK_BLAKE = 20;
	static constexpr float JUMP_POWER = 350;

	AnimationClip m_animClip[int(Anim::Num)];        //�A�j���[�V�����N���b�v

	ModelArmWeapon m_sword;
	Shield m_shield;

	PlayerCamera m_camera;                      //�J����

	BarGauge m_hpBar;//HP�o�[

	Stamina m_stamina;//�X�^�~�i

	SoundOverlap m_se_swordSwing;
	SoundOverlap m_se_swordSlash;
	SoundOverlap m_se_guard;

	bool m_fallDeath = false; //������
};

