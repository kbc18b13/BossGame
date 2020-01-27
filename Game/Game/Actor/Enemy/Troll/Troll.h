#pragma once
#include "Actor/Actor.h"
#include "Util/CharaConEx.h"
#include "TrollBodyCollision.h"
#include "Util/BarGauge.h"
#include "graphics/FontRender.h"
#include "Weapon/ArmWeapon.h"

namespace TrollAct{
class Act;
}

class Troll : public Actor{
public:
	//�֐�
	Troll( IStage* stage );
	~Troll();

	void Start() override;
	void Update() override;

	//��
	enum class AnimState{
		Walk,
		Attack,
		JumpUp,
		JumpDown,
		Idle,
		Tackle,
		Hip,
		Num
	};

	enum class ActState{
		Wait,
		Chase,
		Attack,
		Step,
		Tackle,
		Hip,
		Num,
	};

private:
	/// <summary>
	/// �f�t�H���g�̃X�e�[�g�ύX
	/// </summary>
	void ChangeActDefault();

	/// <summary>
	/// �w�莮�X�e�[�g�ύX
	/// </summary>
	/// <param name="act"></param>
	void ChangeAct( ActState  act);

	//���݂̃X�e�[�g
	TrollAct::Act* m_activeAction;
	//�X�e�[�g�z��
	std::unique_ptr<TrollAct::Act> m_actionArray[int( ActState::Num )];

	AnimationClip m_animClip[int( AnimState::Num )];//�A�j���[�V�����N���b�v

	ArmWeapon m_armCollision;//�r�̍U������
	TrollBodyCollision m_bodyCollision;//�̂̍U������

	BarGauge m_hpBar; //HP�o�[
	FontRender m_nameFont;

	friend class TrollAct::Act;
};