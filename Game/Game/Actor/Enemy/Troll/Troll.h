#pragma once
#include "Actor/Actor.h"
#include "Util/CharaConEx.h"
#include "TrollArmCollision.h"
#include "TrollBodyCollision.h"
#include "Util/BarGauge.h"

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

	void SetPos( const CVector3& pos ) override;

	CVector3 GetPos() const override{
		return m_CharaCon.GetPosition();
	}

	/// <summary>
	/// ����������
	/// </summary>
	void AddVelocity( const CVector3& pos ) override{
		m_CharaCon.AddVelocity( pos );
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

	CharaConEx m_CharaCon;//�L�����N�^�[�R���g���[���[
	AnimationClip m_animClip[int( AnimState::Num )];//�A�j���[�V�����N���b�v
	SkinModelRender m_model;//���f��

	TrollArmCollision m_armCollision;//�r�̍U������
	TrollBodyCollision m_bodyCollision;//�̂̍U������

	BarGauge m_hpBar; //HP�o�[

	bool m_isDeath = false; //����ł���Ȃ�true

	friend class TrollAct::Act;
};