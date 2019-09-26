#pragma once
#include "Camera/PlayerCamera.h"
#include "character/CharacterController.h"
#include "Util/ResistVector3.h"

class SkinModelRender;

class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Update() override;

	/// <summary>
	/// 位置を取得
	/// </summary>
	CVector3 GetPos() {
		return m_charaCon.GetPosition();
	}

	/// <summary>
	/// 位置を設定
	/// </summary>
	void SetPos(const CVector3& pos) {
		m_charaCon.SetPosition(pos);
	}

private:
	static constexpr float WALK_MAX = 200;
	static constexpr float WALK_ACCEL_AIR = 10;
	static constexpr float WALK_ACCEL = 50;
	static constexpr float WALK_BLAKE = 20;
	static constexpr float JUMP_POWER = 350;

	CVector3 m_walkSpeed;//移動速度
	float jumpSpeed = 0;
	CQuaternion rot;//回転

	enum EnAnim {
		enAnimWalk,
		enAnimSlash,
		enAnimNum
	};
	AnimationClip m_animClip[enAnimNum];        //アニメーションクリップ
	SkinModelRender* m_model;                    //自分のモデル。
	SkinModel m_swordModel;                    //剣のモデル。

	CharacterController m_charaCon;             //キャラコン

	PlayerCamera m_camera;                      //カメラ
};

