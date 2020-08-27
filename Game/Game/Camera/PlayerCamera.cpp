#include "stdafx.h"
#include "PlayerCamera.h"
#include "Scene/IStage.h"
#include <numeric>

PlayerCamera::PlayerCamera(){
	m_lockOnSprite.Init( L"Assets/sprite/lockOn.dds", 80, 80 );
	m_lockOnSprite.SetScale( CVector2( 0.5f, 0.5f ) );
	m_lockOnSprite.SetIsDraw( false );
}

void PlayerCamera::UpdateGCamera( const CVector3& pos, const CVector3& look){

	//レイキャストを使った壁に当たるカメラ
	btCollisionWorld::ClosestRayResultCallback cb(look.toBT(), pos.toBT() );
	cb.m_collisionFilterMask = 0xffffffff;
	cb.m_collisionFilterMask ^= btCollisionObject::CollisionFlags::CF_Player;
	cb.m_collisionFilterGroup = btCollisionObject::CollisionFlags::CF_Camera;

	g_physics.GetDynamicWorld()->rayTest( look.toBT(), pos.toBT(), cb );

	if( cb.hasHit() ){
		//例が当たったから少し押しもどす。
		CVector3 hitPos(cb.m_hitPointWorld);
		CVector3 toL = look - pos;
		toL.Normalize();
		hitPos += toL * 2;
		g_camera3D.SetPosition( hitPos );
	} else{
		g_camera3D.SetPosition( pos );
	}
	g_camera3D.SetTarget( look );
	g_camera3D.Update();
}

void PlayerCamera::Update(){

	//敵のロックオン
	if( g_pad->IsTrigger( enButtonRB3 ) ){
		TurnLockOn();
	}

	{
		CVector3 playerPos = m_player->GetPos();
		playerPos.y += m_player->GetHeight();

		//バネ位置をプレイヤー側へずらす
		m_springPPos.Lerp( 0.2f, m_springPPos, playerPos );

		//プレイヤーとバネ位置に最大距離を設ける
		CVector3 toSpring = m_springPPos - playerPos;
		if( toSpring.LengthSq() > pow2( 100 ) ){
			toSpring.Normalize();
			toSpring *= 100;
			m_springPPos = playerPos + toSpring;
		}
	}

	//ロックオン中の挙動
	if( IsLockOn() ){
		if( g_pad->IsTriggerRStick() ){
			LockOn( g_pad->GetRStickVec() );
		}

		CVector3 ePos = GetLockOnPos();
		ePos.y += m_lockOnEnemy->GetHeight() / 2;

		m_vec = m_springPPos - ePos;
		m_vec.y = 0;
		m_vec.Normalize();

		CQuaternion::CreateRotDeg( GetRightVec(), 30 ).Multiply( m_vec );

		m_vec *= CtoPLength;
		m_pos = m_springPPos + m_vec;

		//バネ回転
		m_springVec.Lerp( 0.7f, m_springVec, m_vec );

		//カメラの更新。
		UpdateGCamera( m_springPPos + m_springVec, m_springPPos );

		//ターゲット画像の移動
		m_lockOnSprite.SetPosNormalized( g_camera3D.GetProjectedPos( ePos ).xy() );
		return;
	}

	//非ロックオン中の挙動

	//回り込みカメラ
	CVector3 PtoC = m_pos - m_springPPos;
	PtoC.Normalize();
	PtoC *= CtoPLength;

	//移動後のベクトルと前回のベクトルを合成。yは無視。
	m_vec.x = m_vec.x * 0.3f + PtoC.x * 0.7f;
	m_vec.z = m_vec.z * 0.3f + PtoC.z * 0.7f;

	//縦方向の回転は横に比べて遅くする
	float yVec = m_vec.y * 0.7f + PtoC.y * 0.3f;

	//縦方向の回転は、一定範囲内に収まっていなければ無効にする。
	constexpr float cos80 = 0.1736481f;
	constexpr float cos50 = 0.6427876f;
	if( cos80*CtoPLength < yVec && yVec < cos50*CtoPLength ){
		m_vec.y = yVec;
	}
	m_vec.Normalize();
	m_vec *= CtoPLength;
	
	//スティックによる回転。
	CQuaternion rot;
	rot.SetRotationDeg( CVector3::AxisY(), g_pad->GetRStickXF() * ROT_SPEED * GameTime::GetDeltaTime() );
	rot.AddRotationDeg( GetRightVec(), -g_pad->GetRStickYF() * ROT_SPEED * GameTime::GetDeltaTime() );

	rot.Multiply( m_vec );

	//上下回転に制限をかける。
	float nowPitch = CMath::RadToDeg( acosf( CMath::Clamp( m_vec.y / CtoPLength, -1, 1) ));
	float clampPitch = nowPitch - CMath::Clamp( nowPitch, 90-LIMIT_UP_DOWN_ROT, 90+LIMIT_UP_DOWN_ROT );
	CQuaternion clampRot;
	clampRot.SetRotationDeg( GetRightVec(), clampPitch );

	clampRot.Multiply( m_vec );

	//バネ回転
	m_springVec.Lerp( 0.7f, m_springVec, m_vec );

	//ポジション更新
	m_pos = m_springPPos + m_vec;

	//カメラの更新。
	UpdateGCamera( m_springPPos + m_springVec, m_springPPos );
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
			CVector4 toScreenCenter = g_camera3D.GetProjectedPos( ePos ) - CVector4(pad.x, pad.y, 0, 0);
			//三次元空間での距離
			float toEnemy = ( ePos - pPos ).Length();

			//距離が範囲内の物だけを対象にする。
			if( toEnemy < TARGET_RANGE && toScreenCenter.xy().Length() < 0.8f && toScreenCenter.w > 0){

				float score = toScreenCenter.xy().Length() * 100 + toEnemy;
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
		//既に何かをロックオンしていたら解除する。
		if( m_lockOnEnemy ){
			m_lockOnEnemy->UnLockOn();
		}
		m_lockOnEnemy = lockOn;
		m_lockOnEnemy->LockOn( this );
		m_lockOnSprite.SetIsDraw( true );
	}
}

CVector3 PlayerCamera::GetPadVec(){
	return ( g_pad->GetLStickXF() * GetRightVec() + g_pad->GetLStickYF() * GetFrontVec_XZ() );
}
