/*!
* @brief	キャラクタのコリジョンコントロール。
*/

#include "stdafx.h"
#include "character/CharacterController.h"
#include <numeric>
#include <iostream>

using bcw = btCollisionWorld;

//衝突したときに呼ばれる関数オブジェクト
struct SweepResult : public bcw::ClosestConvexResultCallback{
	const btCollisionObject* me = nullptr;		//自分自身。自分自身との衝突を除外するためのメンバ。

	virtual	btScalar	addSingleResult( btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace ){
		if( convexResult.m_hitCollisionObject == me ){

			return 1.0f;
		}
		return btCollisionWorld::ClosestConvexResultCallback::addSingleResult( convexResult, normalInWorldSpace );
	}
};


void CharacterController::Init(float radius, float height, const CVector3& position, int userIndex,
								void* userPointer, btCollisionObject::CollisionFlags collisionFlag )
{
	m_position = position;
	//コリジョン作成。
	m_radius = radius;
	m_height = height;
	m_collider.Create(radius, height);

	//剛体を初期化。
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_collider;
	rbInfo.mass = 0.0f;
	m_rigidBody.Create(rbInfo);
	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	//剛体の位置を更新。自分のポジションが足元にくるように調整する。
	trans.setOrigin(btVector3(position.x, position.y + radius + height/2, position.z));
	//@todo 未対応。trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
	m_rigidBody.GetBody()->setUserIndex(userIndex);
	m_rigidBody.GetBody()->setUserPointer(userPointer);
	m_rigidBody.GetBody()->setCollisionFlags(collisionFlag);
	g_physics.AddRigidBody(m_rigidBody);

}


const CVector3& CharacterController::Execute(float deltaTime, CVector3& moveSpeed)
{
	if( g_pad->IsPress( enButtonUp ) ){
		m_position.y += 10;
	} else if( g_pad->IsPress( enButtonDown ) ){
		m_position.y -= 10;
	}

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
	CVector3 startPos(m_position.x, m_position.y + m_height * 0.5f + m_radius, m_position.z);
	CVector3 addVec = moveSpeed * deltaTime;
	CVector3 nextPos = startPos + addVec;

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

	//当たった。
	if( sweepResult.hasHit()){
		//めり込みを押し戻す
		CVector3 moveBack = -addVec * (1 - sweepResult.m_closestHitFraction) * 1.2f; //めり込みぶんのベクトルの逆

		CVector3 hitNormal(sweepResult.m_hitNormalWorld);
		CVector3 normalMoveBack = hitNormal * ( moveBack ).Dot( hitNormal );//法線に投影。

		//めり込み直しによる壁づたいの移動を判定する
		bool hasHit = false;
		SweepResult sweepResult2;
		if( ( normalMoveBack - moveBack ).LengthSq() > 0.00001f){

			btTransform btStart;
			btTransform btEnd;
			btStart.setIdentity();
			btEnd.setIdentity();
			btStart.setOrigin( ( nextPos + moveBack ).toBT() );
			btEnd.setOrigin( ( nextPos + normalMoveBack ).toBT() );

			//コールバック
			sweepResult2.me = m_rigidBody.GetBody();
			sweepResult2.m_collisionFilterGroup = m_rigidBody.GetBody()->getCollisionFlags();
			g_physics.ConvexSweepTest( (const btConvexShape*)m_collider.GetBody(), btStart, btEnd, sweepResult2 );
			hasHit = sweepResult2.hasHit();
		}

		//壁づたいの移動でも当たった。
		//次のポリゴンの法線と、前のポリゴンの法線がなす角度が一定以上なら地続きとみなす。
		if( hasHit &&
			acosf(CVector3(sweepResult2.m_hitNormalWorld).Dot(hitNormal)) > CMath::DegToRad(10)){

			//接地判定用に法線を更新
			hitNormal.Set( sweepResult2.m_hitNormalWorld );

			//今回は衝突点で止めるだけなので、純粋に移動量を求める。
			CVector3 addVec2 = normalMoveBack - moveBack;
			CVector3 move = addVec * sweepResult2.m_closestHitFraction;

			nextPos += moveBack + move;
		} else{
			nextPos += normalMoveBack;
		}

		//接地判定
		const float upDot = CVector3::Up().Dot( hitNormal );
		if( moveSpeed.y < 0.0f && acosf( upDot ) < CMath::DegToRad( 50 ) ){
			m_isJump = false;
			m_isOnGround = true;
			moveSpeed.y = 0;
		}
	}

	//移動確定。
	//ポジションを足元に戻す。
	m_position.Set( nextPos.x, nextPos.y - (m_radius + m_height / 2), nextPos.z );
	btRigidBody* btBody = m_rigidBody.GetBody();
	//剛体を動かす。
	btBody->setActivationState( DISABLE_DEACTIVATION );
	btTransform& trans = btBody->getWorldTransform();
	//剛体の位置を更新。
	trans.setOrigin( nextPos.toBT());

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

