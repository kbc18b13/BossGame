#include "stdafx.h"
#include "PlayerCamera.h"

void PlayerCamera::Update(const CVector3 & playerPos) {
	//位置の更新
	m_pos = playerPos + m_vec;
	g_camera3D.SetTarget(playerPos);
	g_camera3D.SetPosition(m_pos);

	//回転の更新
	CQuaternion rot;
	rot.SetRotationDeg(CVector3::AxisY(), g_pad->GetRStickXF() * ROT_SPEED * GameTime::GetDeltaTime());
	//上下回転を制限
	float addRot = -g_pad->GetRStickYF() * ROT_SPEED * GameTime::GetDeltaTime();
	float addedRot = m_UpDownRot + addRot;
	m_UpDownRot = CMath::Clamp(addedRot, -LIMIT_UP_DOWN_ROT, LIMIT_UP_DOWN_ROT);
	addRot -= addedRot - m_UpDownRot;
	rot.AddRotationDeg(GetRightVec(), addRot);
	//回転の実行
	rot.Multiply(m_vec);
}
