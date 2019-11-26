#pragma once
#include "Actor/Actor.h"
#include "graphics/CFont.h"
#include "Util/CharaConEx.h"
#include "TrollArmCollision.h"
class SkinModelRender;
class Stage1;
class Act;

class Troll: public Actor {
public:
	//関数
	Troll(Stage1* stage);
	~Troll();

	void Start() override;
	void Update() override;
	void Draw() override;

	void SetPos(const CVector3& pos) override;

	CVector3 GetPos() const override {
		return m_CharaCon.GetPosition();
	}

    /// <summary>
    /// 加速させる
    /// </summary>
    void AddVelocity(const CVector3& pos) override {
        m_CharaCon.AddVelocity(pos);
    }

	//列挙
	enum class AnimState {
		Walk,
		Attack,
		JumpUp,
		JumpDown,
		Idle,
        Tackle,
        Hip,
		Num
	};

	enum class ActState {
		Wait,
		Chase,
		Attack,
		Step,
        Tackle,
        Hip,
		Num,
	};

private:
	//変数
	Stage1* stage;

    Act* m_activeAction;
    std::unique_ptr<Act> m_actionArray[int(ActState::Num)];
	std::function<void(ActState)> m_stateChangeFunc;

	int m_state;

	float m_timer = 0.0f;

	CharaConEx m_CharaCon;
	AnimationClip m_animClip[int(AnimState::Num)];//アニメーションクリップ
	SkinModelRender m_model;//モデル

	CFont m_font;

    TrollArmCollision armCollision;
};