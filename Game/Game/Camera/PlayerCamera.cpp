#include "stdafx.h"
#include "PlayerCamera.h"
#include "Scene/IStage.h"
#include "Actor/Actor.h"

void PlayerCamera::Update(const CVector3 & playerPos) {
	//�ʒu�̍X�V
	m_pos = playerPos + m_vec;
	g_camera3D.SetTarget(playerPos);
	g_camera3D.SetPosition(m_pos);

	//��]�̍X�V
	CQuaternion rot;
	rot.SetRotationDeg(CVector3::AxisY(), g_pad->GetRStickXF() * ROT_SPEED * GameTime::GetDeltaTime());
	//�㉺��]�𐧌�
	float addRot = -g_pad->GetRStickYF() * ROT_SPEED * GameTime::GetDeltaTime();
	float addedRot = m_UpDownRot + addRot;
	m_UpDownRot = CMath::Clamp(addedRot, -LIMIT_UP_DOWN_ROT, LIMIT_UP_DOWN_ROT);
	addRot -= addedRot - m_UpDownRot;
	rot.AddRotationDeg(GetRightVec(), addRot);
	//��]�̎��s
	rot.Multiply(m_vec);

	//�J�����̍X�V�B
	g_camera3D.Update();
}

void PlayerCamera::TargetEnemy( IStage & stage ){
	for( Actor* e : stage.GetEnemys() ){
		CVector3 pos = e->GetPos();
	}
}
