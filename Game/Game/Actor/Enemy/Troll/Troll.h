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
	//関数
	Troll( IStage* stage );
	~Troll();

	void Start() override;
	void Update() override;

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
	/// <summary>
	/// デフォルトのステート変更
	/// </summary>
	void ChangeActDefault();

	/// <summary>
	/// 指定式ステート変更
	/// </summary>
	/// <param name="act"></param>
	void ChangeAct( ActState  act);

	//現在のステート
	TrollAct::Act* m_activeAction;
	//ステート配列
	std::unique_ptr<TrollAct::Act> m_actionArray[int( ActState::Num )];

	AnimationClip m_animClip[int( AnimState::Num )];//アニメーションクリップ

	ArmWeapon m_armCollision;//腕の攻撃判定
	TrollBodyCollision m_bodyCollision;//体の攻撃判定

	BarGauge m_hpBar; //HPバー
	FontRender m_nameFont;

	friend class TrollAct::Act;
};