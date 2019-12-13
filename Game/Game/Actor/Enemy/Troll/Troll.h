#pragma once
#include "Actor/Actor.h"
#include "Util/CharaConEx.h"
#include "TrollArmCollision.h"
#include "Util/BarGauge.h"
class SkinModelRender;
class Stage1;

namespace TrollAct{
class Act;
}

class Troll : public Actor{
public:
	//関数
	Troll( Stage1* stage );
	~Troll();

	void Start() override;
	void Update() override;

	void SetPos( const CVector3& pos ) override;

	CVector3 GetPos() const override{
		return m_CharaCon.GetPosition();
	}

	/// <summary>
	/// 加速させる
	/// </summary>
	void AddVelocity( const CVector3& pos ) override{
		m_CharaCon.AddVelocity( pos );
	}

	//列挙
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
	void ChangeActDefault();
	void ChangeAct( ActState  act);

	//変数
	Stage1* stage;

	TrollAct::Act* m_activeAction;
	std::unique_ptr<TrollAct::Act> m_actionArray[int( ActState::Num )];

	int m_state;

	float m_timer = 0.0f;

	CharaConEx m_CharaCon;
	AnimationClip m_animClip[int( AnimState::Num )];//アニメーションクリップ
	SkinModelRender m_model;//モデル

	TrollArmCollision armCollision;

	BarGauge m_hpBar; //HPバー

	friend class TrollAct::Act;
};