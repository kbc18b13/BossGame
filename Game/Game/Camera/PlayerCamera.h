#pragma once
#include "graphics/SpriteRender.h"
#include "Actor/Actor.h"

class IStage;

class PlayerCamera {
public:
	PlayerCamera();

	/// <summary>
	/// プレイヤー座標を与えてカメラ位置を更新する
	/// </summary>
	/// <param name="playerPos">プレイヤーの位置</param>
	void Update(const CVector3& playerPos);

	/// <summary>
	/// プレイヤーからカメラへのベクトルを設定する。
	/// </summary>
	/// <param name="vec">プレイヤーからカメラへのベクトル</param>
	void SetVec(CVector3 vec) {
		m_vec = vec;
		vec.Normalize();
		m_UpDownRot = CMath::RadToDeg(acosf(CVector3::AxisY().Dot(vec)));
	}

	void TurnLockOn(IStage* stage);

	/// <summary>
	/// カメラの前方向
	/// </summary>
	/// <returns></returns>
	CVector3 GetFrontVec_XZ() {
		CVector3 front = -m_vec;
		front.y = 0;
		front.Normalize();
		return front;
	}

	/// <summary>
	/// カメラの右方向
	/// </summary>
	/// <returns></returns>
	CVector3 GetRightVec() {
		CVector3 right = CVector3::AxisY();
		right.Cross(-m_vec);
		right.Normalize();
		return right;
	}

	/// <summary>
	/// ロックオン中ならTrue
	/// </summary>
	bool IsLockOn(){
		return m_lockOnEnemy != nullptr;
	}

	/// <summary>
	/// ロックオン対象の位置を取得。ロックオン中以外はエラー。
	/// </summary>
	CVector3 GetLockOnPos(){
		return m_lockOnEnemy->GetPos();
	}

private:
	static constexpr float ROT_SPEED = 180;//カメラ回転スピード。度/秒。
	static constexpr float LIMIT_UP_DOWN_ROT = 80;//上下回転の制限。度。0度～90度。
	static constexpr int TARGET_RANGE = 400; //ターゲット可能な距離

	float m_UpDownRot = 0.0f; //上下の回転。度。

	CVector3 m_vec = {0,0,-100};//プレイヤーからカメラへのベクトル
	CVector3 m_pos;//カメラの位置

	Actor* m_lockOnEnemy = nullptr;

	SpriteRender m_lockOnSprite;
};