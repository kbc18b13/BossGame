/*!
* @brief	キャラクタのコリジョンコントロール。
*/

#include "stdafx.h"
#include "character/CharacterController.h"

using bcw = btCollisionWorld;

//衝突したときに呼ばれる関数オブジェクト
struct SweepResult : public bcw::ClosestConvexResultCallback{
	const btCollisionObject* me = nullptr;		//自分自身。自分自身との衝突を除外するためのメンバ。

	virtual	btScalar	addSingleResult( bcw::LocalConvexResult& convexResult, bool normalInWorldSpace ){
		if( convexResult.m_hitCollisionObject == me ){

			return 1.0f;
		}
		return bcw::ClosestConvexResultCallback::addSingleResult( convexResult, normalInWorldSpace );
	}
};


void CharacterController::Init( float radius, float height, const CVector3& position, int userIndex,
								void* userPointer, btCollisionObject::CollisionFlags collisionFlag ){
	m_position = position;
	//コリジョン作成。
	m_radius = radius;
	m_height = height;
	m_collider.Create( radius, height );

	//剛体を初期化。
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_collider;
	rbInfo.mass = 0.0f;
	m_rigidBody.Create( rbInfo );
	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	//剛体の位置を更新。自分のポジションが足元にくるように調整する。
	trans.setOrigin( btVector3( position.x, position.y + radius + height / 2, position.z ) );
	//@todo 未対応。trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
	m_rigidBody.GetBody()->setUserIndex( userIndex );
	m_rigidBody.GetBody()->setUserPointer( userPointer );
	m_rigidBody.GetBody()->setCollisionFlags( collisionFlag );
	g_physics.AddRigidBody( m_rigidBody );

}

const CVector3& CharacterController::Execute( float deltaTime, CVector3& moveSpeed ){

	if( moveSpeed.LengthSq() < 0.00001f ){
		return m_position;
	}

	if( moveSpeed.y > 0.0f ){
		//吹っ飛び中にする。
		m_isJump = true;
		m_isOnGround = false;
	}

	//次の移動先となる座標を計算する。
	//カプセルの中心の位置で考える。
	CVector3 startPos( m_position.x, m_position.y + m_height * 0.5f + m_radius, m_position.z );
	CVector3 nextPos = startPos + moveSpeed * deltaTime;

	//このフレームでの接地判定
	bool frameOnGround = false;

	//衝突判定。
	for( int i = 0 ; i < 10; i++ ){

		//動きが少なすぎたら判定せず終了。
		CVector3 addVec = nextPos - startPos;
		if( addVec.LengthSq() < 0.00001f ){
			break;
		}

		//衝突判定。
		SweepResult sweepResult;
		{
			//SweepTest用の始点と終点
			btTransform btStart;
			btTransform btEnd;
			btStart.setIdentity();
			btEnd.setIdentity();
			btStart.setOrigin( startPos.toBT() );
			btEnd.setOrigin( nextPos.toBT() );

			//コールバックの設定
			sweepResult.me = m_rigidBody.GetBody();
			sweepResult.m_collisionFilterGroup = m_rigidBody.GetBody()->getCollisionFlags();

			//判定
			g_physics.ConvexSweepTest( (const btConvexShape*)m_collider.GetBody(), btStart, btEnd, sweepResult );
		}

		//当たらなかったら終了。
		if( !sweepResult.hasHit() ){
			break;
		}

		//面の法線
		CVector3 hitNormal( sweepResult.m_hitNormalWorld );

		//接地の判定。接触面の法線と上方向が一定角度以内なら地面とみなす。
		if( !frameOnGround && acosf( hitNormal.Dot( CVector3::Up() ) ) < CMath::DegToRad( 45 ) ){
			m_isJump = false;
			m_isOnGround = true;
			frameOnGround = true;
			moveSpeed.y = 0;
		}

		//めり込みを押し戻す
		CVector3 moveBack = -addVec * ( 1 - sweepResult.m_closestHitFraction ); //めり込みぶんのベクトルの逆

		//移動方向が下向きなら立っているだけとみなし、法線投影を行わない。(坂で自重で滑ったりしない。)
		if( IsOnGround() && acosf( addVec.GetNormalized().Dot( CVector3::Down() ) ) < CMath::DegToRad( 10 ) ){
			nextPos += moveBack;
			break;
		}

		CVector3 normalMoveBack = hitNormal * ( moveBack ).Dot( hitNormal );//法線に投影。

		//2回目の判定で今のポリゴンと触れないように法線方向に少し浮かせる。
		startPos = nextPos + moveBack + hitNormal*0.1f;
		nextPos = nextPos + normalMoveBack + hitNormal*0.1f;
	}

	//接地してない判定。
	if( !frameOnGround )m_isOnGround = false;

	//移動確定。
	//ポジションを足元に戻す。
	m_position.Set( nextPos.x, nextPos.y - ( m_radius + m_height / 2 ), nextPos.z );
	btRigidBody* btBody = m_rigidBody.GetBody();
	//剛体を動かす。
	btBody->setActivationState( DISABLE_DEACTIVATION );
	btTransform& trans = btBody->getWorldTransform();
	//剛体の位置を更新。
	trans.setOrigin( nextPos.toBT() );

	return m_position;
}

void CharacterController::SetActive( bool active ){
	if( m_isActive && !active ){
		g_physics.RemoveRigidBody( m_rigidBody );
	}
	if( !m_isActive && active ){
		g_physics.AddRigidBody( m_rigidBody );
	}
	m_isActive = active;
}

