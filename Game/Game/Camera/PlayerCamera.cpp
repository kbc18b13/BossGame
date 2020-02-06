#include "stdafx.h"
#include "PlayerCamera.h"
#include "Scene/IStage.h"
#include <numeric>

PlayerCamera::PlayerCamera(){
	m_lockOnSprite.Init( L"Assets/sprite/lockOn.dds", 80, 80 );
	m_lockOnSprite.SetScale( CVector2( 0.5f, 0.5f ) );
	m_lockOnSprite.SetIsDraw( false );
}

void PlayerCamera::UpdateGCamera(const CVector3& look){

	//レイキャストを使った壁に当たるカメラ
	btCollisionWorld::ClosestRayResultCallback cb(look, m_pos);

	g_physics.GetDynamicWorld()->rayTest( look, m_pos, cb );

	if( cb.hasHit() ){
		//例が当たったから少し押しもどす。
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

void PlayerCamera::Update(){

	//敵のロックオン
	if( g_pad->IsTrigger( enButtonRB3 ) ){
		TurnLockOn();
	}

	CVector3 playerPos = m_player->GetPos();
	playerPos.y += m_player->GetHeight();

	//ロックオン中の挙動
	if( IsLockOn() ){
		if( g_pad->IsTriggerRStick() ){
			LockOn( g_pad->GetRStickVec() );
		}

		CVector3 ePos = GetLockOnPos();
		ePos.y += m_lockOnEnemy->GetHeight() / 2;

		m_vec = playerPos - ePos;
		m_vec.y = 0;
		m_vec.Normalize();

		CQuaternion::CreateRotDeg( GetRightVec(), 30 ).Multiply( m_vec );

		m_vec *= 100;
		m_pos = playerPos + m_vec;

		//カメラの更新。
		UpdateGCamera( playerPos );

		//ターゲット画像の移動
		m_lockOnSprite.SetPosNormalized( g_camera3D.GetProjectedPos( ePos ).xy() );
		return;
	}

	//非ロックオン中の挙動

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

void PlayerCamera::LockOn(CVector2 pad ){
	float lockScore = std::numeric_limits<float>::max();
	Actor* lockOn = nullptr;

	//スクリーン上の距離計算の際に中心をずらすことで、パッド入力でターゲット切り替えを行えるようにする。
	if( pad.LengthSq() > pow2(0.01f) ){
		pad.Normalize();
		pad *= 0.4f;
	}

	for( Actor* e : m_player->GetStage()->GetEnemys() ){
		CVector3 ePos = e->GetPos();
		CVector3 pPos = m_pos - m_vec;

		//死亡者以外、現在ロック中以外
		if( !e->IsDeath()  && e != m_lockOnEnemy){

			//スクリーン上での距離
			CVector2 toScreenCenter = g_camera3D.GetProjectedPos( ePos ).xy() - pad;
			//三次元空間での距離
			float toEnemy = ( ePos - pPos ).Length();

			//距離が範囲内の物だけを対象にする。
			if( toEnemy < TARGET_RANGE && toScreenCenter.Length() < 1.0f ){

				float score = toScreenCenter.Length() * 100 + toEnemy;
				//2D、3D乗の距離から算出したスコアが一番小さいものを選ぶ。
				if( lockScore > score ){
					lockOn = e;
					lockScore = score;
				}
			}
		}
	}

	//ロックオン対象が存在した場合
	if( lockOn ){
		if( m_lockOnEnemy ){
			m_lockOnEnemy->UnLockOn();
		}
		m_lockOnEnemy = lockOn;
		m_lockOnEnemy->LockOn( this );
		m_lockOnSprite.SetIsDraw( true );
	}
}

void PlayerCamera::TurnLockOn(){
	//ロックオン解除
	if( IsLockOn() ){
		m_lockOnEnemy->UnLockOn();
		m_lockOnEnemy = nullptr;
		m_lockOnSprite.SetIsDraw( false );
		return;
	}

	//ロックオン
	LockOn();
}

CVector3 PlayerCamera::GetPadVec(){
	return ( g_pad->GetLStickXF() * GetRightVec() + g_pad->GetLStickYF() * GetFrontVec_XZ() );
}
