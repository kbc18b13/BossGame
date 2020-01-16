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
	/// カメラ側から見たパッド操作
	/// </summary>
	/// <returns>ワールド座標系のベクトル</returns>
	CVector3 GetPadVec();

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
	static constexpr float CtoPLength = 100;

	float m_upDownRot = 0.0f; //上下の回転。度。

	CVector3 m_vec = {0,0,-100};//プレイヤーからカメラへのベクトル
	CVector3 m_pos;//カメラの位置

	CVector3 m_oldPlayerPos;

	Actor* m_lockOnEnemy = nullptr;

	SpriteRender m_lockOnSprite;
};