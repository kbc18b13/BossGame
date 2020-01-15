#include "stdafx.h"
#include "PlayerCamera.h"
#include "Scene/IStage.h"
#include <numeric>

PlayerCamera::PlayerCamera(){
	m_lockOnSprite.Init( L"Assets/sprite/lockOn.dds", 80, 80 );
	m_lockOnSprite.SetIsDraw( false );
}

void PlayerCamera::Update( const CVector3 & playerPos){
	if( IsLockOn() ){
		CVector3 ePos = GetLockOnPos();
		ePos.y += 50;
		//ターゲット画像の移動
		m_lockOnSprite.SetPosNormalized( g_camera3D.GetProjectedPos( ePos ).xy() );

		ePos.y = playerPos.y;
		m_vec = playerPos - ePos;
		m_vec.Normalize();

		CQuaternion::CreateRotDeg( GetRightVec(), 30 ).Multiply( m_vec );

		m_vec *= 100;
		m_pos = playerPos + m_vec;

		//カメラの更新。
		g_camera3D.SetTarget( playerPos );
		g_camera3D.SetPosition( m_pos );
		g_camera3D.Update();
		return;
	}

	//位置の更新。いい感じにプレイヤーに追従する。
	CQuaternion rot;
	CVector3 PtoC = m_pos - playerPos;
	PtoC.Normalize();
	//高さは指定する。移動量によって適用されていく。
	float len = ( playerPos - m_oldPlayerPos ).Length();
	PtoC.y += ( CtoPLength*0.4f - PtoC.y ) * len * 0.01f;
	m_oldPlayerPos = playerPos;
	//移動後のベクトルと前回のベクトルを合成。
	PtoC.Normalize();
	m_vec = m_vec * 0.5f + PtoC * 0.5f;
	
	//スティックによる回転
	rot.AddRotationDeg( CVector3::AxisY(), g_pad->GetRStickXF() * ROT_SPEED * GameTime::GetDeltaTime() );
	rot.AddRotationDeg( GetRightVec(), -g_pad->GetRStickYF() * ROT_SPEED * GameTime::GetDeltaTime() );

	rot.Multiply( m_vec );

	m_pos = playerPos + m_vec*CtoPLength;

	g_camera3D.SetTarget( playerPos );
	g_camera3D.SetPosition( m_pos );

	//m_pos = playerPos + m_vec;
	//g_camera3D.SetTarget( playerPos );
	//g_camera3D.SetPosition( m_pos );

	////回転の更新
	//CQuaternion rot;
	//rot.SetRotationDeg( CVector3::AxisY(), g_pad->GetRStickXF() * ROT_SPEED * GameTime::GetDeltaTime() );
	////上下回転を制限
	//float addRot = -g_pad->GetRStickYF() * ROT_SPEED * GameTime::GetDeltaTime();
	//float addedRot = m_UpDownRot + addRot;
	//m_UpDownRot = CMath::Clamp( addedRot, -LIMIT_UP_DOWN_ROT, LIMIT_UP_DOWN_ROT );
	//addRot -= addedRot - m_UpDownRot;
	//rot.AddRotationDeg( GetRightVec(), addRot );
	////回転の実行
	//rot.Multiply( m_vec );

	//カメラの更新。
	g_camera3D.Update();
}

void PlayerCamera::TurnLockOn( IStage* stage ){
	//ロックオン解除
	if( IsLockOn() ){
		m_lockOnEnemy->UnLockOn();
		m_lockOnEnemy = nullptr;
		m_lockOnSprite.SetIsDraw( false );
		return;
	}

	//ロックオン

	float distanceToCenter = std::numeric_limits<float>::max();
	Actor* lockOn = nullptr;

	for( Actor* e : stage->GetEnemys() ){
		CVector3 ePos = e->GetPos();
		CVector3 pPos = m_pos - m_vec;

		//距離が範囲内の物だけを対象にする。
		if( ( ePos - pPos ).LengthSq() < TARGET_RANGE*TARGET_RANGE ){
			CVector2 screenPos = g_camera3D.GetProjectedPos( ePos ).xy();

			//スクリーン座標が中央に一番近い物を選択する。
			if( distanceToCenter > screenPos.LengthSq() ){
				lockOn = e;
				distanceToCenter = screenPos.LengthSq();
			}
		}
	}

	//ロックオン対象が存在した場合
	if( lockOn ){
		m_lockOnEnemy = lockOn;
		m_lockOnEnemy->LockOn( this );
		m_lockOnSprite.SetIsDraw( true );
	}
}

CVector3 PlayerCamera::GetPadVec(){
	return ( g_pad->GetLStickXF() * GetRightVec() + g_pad->GetLStickYF() * GetFrontVec_XZ() );
}
