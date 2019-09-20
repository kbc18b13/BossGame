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
	static constexpr float WALK_SPEED = 20;
	static constexpr float WALK_SPEED_AIR = 2;
	static constexpr float JUMP_SPEED = 10;

	ResistVector3 m_moveSpeed;//移動速度
	CQuaternion rot;//回転

	enum EnAnim {
		enAnimWalk,
		//enAnimRun,
		enAnimNum
	};
	AnimationClip m_animClip[enAnimNum];        //アニメーションクリップ
	std::unique_ptr<SkinModelRender> m_model;	//スキンモデルレンダー。

	CharacterController m_charaCon;             //キャラコン

	PlayerCamera m_camera;                      //カメラ
};

