#include "stdafx.h"
#include "PlayerCamera.h"
#include "Scene/IStage.h"
#include <numeric>

PlayerCamera::PlayerCamera(){
	m_lockOnSprite.Init( L"Assets/sprite/lockOn.dds", 80, 80 );
	m_lockOnSprite.SetIsDraw( false );
}

void PlayerCamera::Update( const CVector3 & playerPos ){
	if( IsLockOn() ){
		CVector3 ePos = GetLockOnPos();
		ePos.y += 50;
		//�^�[�Q�b�g�摜�̈ړ�
		m_lockOnSprite.SetPosNormalized( g_camera3D.GetProjectedPos( ePos ).xy() );

		ePos.y = playerPos.y;
		m_vec = playerPos - ePos;
		m_vec.Normalize();

		CQuaternion::CreateRotDeg( GetRightVec(), 30 ).Multiply( m_vec );

		m_vec *= 100;
		m_pos = playerPos + m_vec;

		//�J�����̍X�V�B
		g_camera3D.SetTarget( playerPos );
		g_camera3D.SetPosition( m_pos );
		g_camera3D.Update();
		return;
	}

	//�ʒu�̍X�V
	m_pos = playerPos + m_vec;
	g_camera3D.SetTarget( playerPos );
	g_camera3D.SetPosition( m_pos );

	//��]�̍X�V
	CQuaternion rot;
	rot.SetRotationDeg( CVector3::AxisY(), g_pad->GetRStickXF() * ROT_SPEED * GameTime::GetDeltaTime() );
	//�㉺��]�𐧌�
	float addRot = -g_pad->GetRStickYF() * ROT_SPEED * GameTime::GetDeltaTime();
	float addedRot = m_UpDownRot + addRot;
	m_UpDownRot = CMath::Clamp( addedRot, -LIMIT_UP_DOWN_ROT, LIMIT_UP_DOWN_ROT );
	addRot -= addedRot - m_UpDownRot;
	rot.AddRotationDeg( GetRightVec(), addRot );
	//��]�̎��s
	rot.Multiply( m_vec );

	//�J�����̍X�V�B
	g_camera3D.Update();
}

void PlayerCamera::TurnLockOn( IStage* stage ){
	//���b�N�I������
	if( IsLockOn() ){
		m_lockOnEnemy->UnLockOn();
		m_lockOnEnemy = nullptr;
		m_lockOnSprite.SetIsDraw( false );
		return;
	}

	//���b�N�I��

	float distanceToCenter = std::numeric_limits<float>::max();
	Actor* lockOn = nullptr;

	for( Actor* e : stage->GetEnemys() ){
		CVector3 ePos = e->GetPos();
		CVector3 pPos = m_pos - m_vec;

		//�������͈͓��̕�������Ώۂɂ���B
		if( ( ePos - pPos ).LengthSq() < TARGET_RANGE*TARGET_RANGE ){
			CVector2 screenPos = g_camera3D.GetProjectedPos( ePos ).xy();

			//�X�N���[�����W�������Ɉ�ԋ߂�����I������B
			if( distanceToCenter > screenPos.LengthSq() ){
				lockOn = e;
				distanceToCenter = screenPos.LengthSq();
			}
		}
	}

	//���b�N�I���Ώۂ����݂����ꍇ
	if( lockOn ){
		m_lockOnEnemy = lockOn;
		m_lockOnEnemy->LockOn( this );
		m_lockOnSprite.SetIsDraw( true );
	}
}

CVector3 PlayerCamera::GetPadVec(){
	return ( g_pad->GetLStickXF() * GetRightVec() + g_pad->GetLStickYF() * GetFrontVec_XZ() );
}
