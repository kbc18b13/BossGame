#pragma once
#include "character/CharacterController.h"

struct CharaConDesc {
	float radius = 0;
	float height = 0;

	CVector3 position;

	int userIndex     = enCollisionAttr_Character;
	void* userPointer = nullptr;

	float walkAccel    = 0;
	float walkAccelAir = 0;
	float walkMax      = 0;

	float jumpPower    = 0;
	float gravity      = 0;
};

class CharaConEx {
public:

    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="desc">初期化パラメータ</param>
	void Init(const CharaConDesc& desc);

    /// <summary>
    /// 移動を実行する
    /// </summary>
    /// <param name="moveXZ">XZ平面を移動</param>
    /// <param name="jump">ジャンプの有無</param>
    /// <returns></returns>
	CVector3 Excecute( const CVector3& moveXZ, bool jump ){
		return Excecute( moveXZ, 1, 1, jump );
	}

	CVector3 Excecute( const CVector3& moveXZ, float maxSpeedScale, float accelScale ,bool jump );

	/// <summary>
	/// moveゼロ、jump無しのExecute。
	/// </summary>
	CVector3 Excecute(){
		return Excecute( CVector3::Zero(), false );
	}

    //位置を設定
	void SetPosition(const CVector3& pos) {
		m_charaCon.SetPosition(pos);
	}

    //位置を取得
	CVector3 GetPosition() const{
		return m_charaCon.GetPosition();
	}

    //速度を取得
	CVector3 GetVelocity() const {
		return CVector3(m_moveSpeedXZ.x, m_jumpSpeed, m_moveSpeedXZ.y);
	}

    //速度を設定
    void SetVelocity(const CVector3& v) {
        m_moveSpeedXZ.x = v.x;
        m_jumpSpeed = v.y;
        m_moveSpeedXZ.y = v.z;
    }

    //加速
    void AddVelocity(const CVector3& v) {
        m_moveSpeedXZ.x += v.x;
        m_jumpSpeed += v.y;
        m_moveSpeedXZ.y += v.z;
    }

	//時間と方向を決めて移動。
	void Move( const CVector3& v, float time ){
		m_timeMoveVec = v;
		m_timeMoveTime = time;
	}

    //着地しているならtrue
	bool OnGround() const {
		return m_charaCon.IsOnGround();
	}

    //重力加速度を取得
    float GetGravity() {
        return m_gravity;
    }

	void SetActive( bool active ){
		m_charaCon.SetActive( active );
	}

	float GetHeight(){
		return m_charaCon.GetHeight();
	}

private:
	float m_walkAccel;
	float m_walkAccelAir;
	float m_walkMax;

	float m_jumpPower;
	float m_gravity;

	CVector2 m_moveSpeedXZ;
	float m_jumpSpeed = 0.0f;

	CVector3 m_timeMoveVec;
	float m_timeMoveTime = 0.0f;

	CharacterController m_charaCon;
};