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
	/// ダメージを与える
	/// </summary>
	/// <param name="damage">ダメージ</param>
	/// <param name="coolTime">ヒット後クールタイム</param>
	/// <returns>クールタイム判定によるダメージの可否</returns>
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
		SlashEnd, //攻撃終了のためのダミー
	};

private:
	::Act* GetAct( int index ) override;
	/// <summary>
	/// デフォルトのステート変更
	/// </summary>
	//void ChangeActDefault();

	/// <summary>
	/// ステート変更
	/// </summary>
	/// <returns>変更に成功したかどうか。スタミナが足りないと失敗する。</returns>
	//bool ChangeAct( Anim act );

	std::unique_ptr<PlayerSpace::PlayerAct> m_actArray[int(Act::Num)];

	static constexpr float WALK_MAX = 200;
	static constexpr float WALK_ACCEL_AIR = 10;
	static constexpr float WALK_ACCEL = 50;
	static constexpr float WALK_BLAKE = 20;
	static constexpr float JUMP_POWER = 350;

	AnimationClip m_animClip[int(Anim::Num)];        //アニメーションクリップ

	ModelArmWeapon m_sword;
	Shield m_shield;

	PlayerCamera m_camera;                      //カメラ

	BarGauge m_hpBar;//HPバー

	Stamina m_stamina;//スタミナ

	SoundOverlap m_se_swordSwing;
	SoundOverlap m_se_swordSlash;
	SoundOverlap m_se_guard;

	bool m_fallDeath = false; //落下死
};

