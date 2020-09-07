#pragma once
#include "graphics/SpriteRender.h"
#include "Actor/Actor.h"

class IStage;

class PlayerCamera {
public:
	PlayerCamera();

	void Init(Actor* player){
		m_player = player;
		CVector3 playerPos = m_player->GetPos();
		playerPos.y += m_player->GetHeight();
		m_springPPos = playerPos;
		m_pos = playerPos + m_vec;
	}

	/// <summary>
	/// プレイヤー座標を与えてカメラ位置を更新する
	/// </summary>
	/// <param name="playerPos">プレイヤーの位置</param>
	void Update();

	/// <summary>
	/// ロックオン状態を切り替える。
	/// </summary>
	void TurnLockOn(){
		if( IsLockOn() ){
			UnLockOn();
			return;
		}
		LockOn();
	}

	/// <summary>
	/// ロックオンを外し、再ロックオンを試す。
	/// </summary>
	void ReLockOn(){
		UnLockOn();
		LockOn( CVector2::Zero(), TARGET_RANGE / 2);
	}

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
		right = right.Cross(-m_vec);
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
	void LockOn(CVector2 pad = CVector2::Zero(), float targetLength = TARGET_RANGE );
	void UnLockOn(){
		m_lockOnEnemy->UnLockOn();
		m_lockOnEnemy = nullptr;
		m_lockOnSprite.SetIsDraw( false );
	}
	void UpdateGCamera( const CVector3& pos, const CVector3& look );

	static constexpr float ROT_SPEED = 180;//カメラ回転スピード。度/秒。
	static constexpr float LIMIT_UP_DOWN_ROT = 70;//上下回転の制限。度。0度～90度。
	static constexpr int TARGET_RANGE = 800; //ターゲット可能な距離
	static constexpr float CtoPLength = 70; //プレイヤーからカメラへのベクトルの長さ

	Actor* m_player = nullptr;
	CVector3 m_springPPos; //プレイヤーに遅れてついていくポジション

	CVector3 m_vec = {0,0,-CtoPLength };//プレイヤーからカメラへのベクトル
	CVector3 m_springVec = { 0,0,-CtoPLength }; //カメラ回転に遅れてついていくベクトル
	CVector3 m_pos;//カメラの位置

	Actor* m_lockOnEnemy = nullptr;

	SpriteRender m_lockOnSprite;
};