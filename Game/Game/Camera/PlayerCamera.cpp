#include "stdafx.h"
#include "PlayerCamera.h"
#include "Scene/IStage.h"
#include <numeric>

PlayerCamera::PlayerCamera(){
	m_lockOnSprite.Init( L"Assets/sprite/lockOn.dds", 80, 80 );
	m_lockOnSprite.SetIsDraw( false );
}

void PlayerCamera::UpdateGCamera(const CVector3& look){

	btCollisionWorld::ClosestRayResultCallback cb(look, m_pos);

	g_physics.GetDynamicWorld()->rayTest( look, m_pos, cb );

	if( cb.hasHit() ){
		CVector3 hitPos = cb.m_hitPointWorld;
		CVector3 toL = look - m_pos;
		toL.Normalize();
		hitPos += toL * 2;
		g_camera3D.SetPosition( hitPos );
	} else{
		g_camera3D.SetPosition( m_pos );
	}
	g_camera3D.SetTarget( look );
	g_camera3D.Update();
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
		UpdateGCamera( playerPos );
		return;
	}

	//回り込みカメラ
	CVector3 PtoC = m_pos - playerPos;
	PtoC.y = 0;
	PtoC.Normalize();
	PtoC *= CtoPLength;
	//移動後のベクトルと前回のベクトルを合成。yは無視。
	float nowYRot = m_vec.y;
	m_vec = m_vec * 0.3f + PtoC * 0.7f;
	m_vec.y = nowYRot;
	
	//スティックによる回転。ここは横回転。
	CQuaternion rot = CQuaternion::CreateRotDeg( CVector3::AxisY(), g_pad->GetRStickXF() * ROT_SPEED * GameTime::GetDeltaTime() );
	rot.Multiply( m_vec );

	//上下回転はfloatで保持して制限をかける。
	m_upDownRot -= g_pad->GetRStickYF() * ROT_SPEED * GameTime::GetDeltaTime();
	m_upDownRot = CMath::Clamp( m_upDownRot, -LIMIT_UP_DOWN_ROT, LIMIT_UP_DOWN_ROT );
	rot.SetRotationDeg( GetRightVec(), m_upDownRot );
	CVector3 upDownRoteteVec = m_vec;
	rot.Multiply( upDownRoteteVec );

	//ポジション更新
	m_pos = playerPos + upDownRoteteVec;

	//カメラの更新。
	UpdateGCamera( playerPos );
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

		//死亡者以外
		if( !e->IsDeath() ){
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
