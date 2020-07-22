#pragma once
#include "Actor/Actor.h"
#include "Util/CharaConEx.h"
#include "TrollBodyCollision.h"
#include "Util/BarGauge.h"
#include "graphics/FontRender.h"
#include "Weapon/ArmWeapon.h"

namespace EnemySpace{
class EnemyAct;
}

class Troll : public Actor{
public:
	//�֐�
	Troll( IStage* stage );
	~Troll();

	void Start() override;
	void Update() override;
	void OnDeath() override;

	void SetDeathFunc( std::function<void()> func ){
		m_deathFunc = func;
	}

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
	Act* GetAct( int index ) override;

	//���݂̃X�e�[�g
	EnemySpace::EnemyAct* m_activeAction;
	//�X�e�[�g�z��
	std::unique_ptr<EnemySpace::EnemyAct> m_actionArray[int( ActState::Num )];

	AnimationClip m_animClip[int( AnimState::Num )];//�A�j���[�V�����N���b�v

	ArmWeapon m_armCollision;//�r�̍U������
	TrollBodyCollision m_bodyCollision;//�̂̍U������

	BarGauge m_hpBar; //HP�o�[
	FontRender m_nameFont;

	std::function<void()> m_deathFunc;
};