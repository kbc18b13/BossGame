#include "stdafx.h"
#include "CharaConEx.h"

void CharaConEx::Init(const CharaConDesc& desc) {
	m_charaCon.Init(desc.radius, desc.height, desc.position, desc.userIndex, desc.userPointer);
	m_walkAccel    = desc.walkAccel;
	m_walkAccelAir = desc.walkAccelAir;
	m_walkBrake    = desc.walkBrake;
	m_walkMax      = desc.walkMax;
	m_jumpPower    = desc.jumpPower;
	m_gravity      = desc.gravity;
}

CVector3 CharaConEx::Excecute(const CVector2& pad, bool jump) {
	//歩行
	{
		//空中と接地でスピードを分ける
		const float accel = m_charaCon.IsOnGround() ? m_walkAccel : m_walkAccelAir;

		//最大速度。外因によってWALK_MAXを超過している場合、それを妨げない。
		const float maxSpeed = max(m_walkMax, m_moveSpeedXZ.Length());

		//加速処理
		m_moveSpeedXZ += pad * accel;

		const float len = m_moveSpeedXZ.Length();//移動ベクトルの長さ

		if (len > 0.1f) {//停止していない場合

			//減速処理
			CVector2 norm = m_moveSpeedXZ / len;
			CVector2 beforeSpeed = m_moveSpeedXZ;
			m_moveSpeedXZ -= norm * m_walkBrake;
			if (m_moveSpeedXZ.Dot(beforeSpeed) < 0) {//減速の結果逆方向に行ったら停止する。
				m_moveSpeedXZ = CVector2(0, 0);
			}


			if (len > maxSpeed) {//上限以上のスピードが出ているなら抑える。
				m_moveSpeedXZ /= len;
				m_moveSpeedXZ *= maxSpeed;
			}
		}
	}

	//上下
	{
		m_jumpSpeed -= m_gravity * GameTime::GetDeltaTime();
		if (jump) {
			m_jumpSpeed += m_jumpPower;
		}
	}

	CVector3 prop(m_moveSpeedXZ.x, m_jumpSpeed, m_moveSpeedXZ.y);
	m_charaCon.Execute(GameTime::GetDeltaTime(), prop);
	m_jumpSpeed = prop.y;
	return m_charaCon.GetPosition();
}
