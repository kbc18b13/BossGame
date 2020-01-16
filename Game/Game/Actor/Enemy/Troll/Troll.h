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
	//関数
	Troll( IStage* stage );
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

	CharaConEx m_CharaCon;//キャラクターコントローラー
	AnimationClip m_animClip[int( AnimState::Num )];//アニメーションクリップ
	SkinModelRender m_model;//モデル

	TrollArmCollision m_armCollision;//腕の攻撃判定
	TrollBodyCollision m_bodyCollision;//体の攻撃判定

	BarGauge m_hpBar; //HPバー

	bool m_isDeath = false; //死んでいるならtrue

	friend class TrollAct::Act;
};