/*!
* @brief	�L�����N�^�̃R���W�����R���g���[���B
*/

#include "stdafx.h"
#include "character/CharacterController.h"
#include <numeric>
#include <iostream>

using bcw = btCollisionWorld;

//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g
struct SweepResult : public bcw::ClosestConvexResultCallback{
	const btCollisionObject* me = nullptr;		//�������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o�B

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
	//�R���W�����쐬�B
	m_radius = radius;
	m_height = height;
	m_collider.Create(radius, height);

	//���̂��������B
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_collider;
	rbInfo.mass = 0.0f;
	m_rigidBody.Create(rbInfo);
	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	//���̂̈ʒu���X�V�B�����̃|�W�V�����������ɂ���悤�ɒ�������B
	trans.setOrigin(btVector3(position.x, position.y + radius + height/2, position.z));
	//@todo ���Ή��Btrans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
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
		//������ђ��ɂ���B
		m_isJump = true;
		m_isOnGround = false;
	}

	//���̈ړ���ƂȂ���W���v�Z����B
	//�J�v�Z���̒��S�̈ʒu�ōl����B
	CVector3 startPos(m_position.x, m_position.y + m_height * 0.5f + m_radius, m_position.z);
	CVector3 addVec = moveSpeed * deltaTime;
	CVector3 nextPos = startPos + addVec;

	//�Փ˔���B
	SweepResult sweepResult;
	{
		//SweepTest�p�̎n�_�ƏI�_
		btTransform btStart;
		btTransform btEnd;
		btStart.setIdentity();
		btEnd.setIdentity();
		btStart.setOrigin( startPos.toBT() );
		btEnd.setOrigin( nextPos.toBT() );

		//�R�[���o�b�N�̐ݒ�
		sweepResult.me = m_rigidBody.GetBody();
		sweepResult.m_collisionFilterGroup = m_rigidBody.GetBody()->getCollisionFlags();

		//����
		g_physics.ConvexSweepTest( (const btConvexShape*)m_collider.GetBody(), btStart, btEnd, sweepResult );
	}

	//���������B
	if( sweepResult.hasHit()){
		//�߂荞�݂������߂�
		CVector3 moveBack = -addVec * (1 - sweepResult.m_closestHitFraction) * 1.2f; //�߂荞�݂Ԃ�̃x�N�g���̋t

		CVector3 hitNormal(sweepResult.m_hitNormalWorld);
		CVector3 normalMoveBack = hitNormal * ( moveBack ).Dot( hitNormal );//�@���ɓ��e�B

		//�߂荞�ݒ����ɂ��ǂÂ����̈ړ��𔻒肷��
		bool hasHit = false;
		SweepResult sweepResult2;
		if( ( normalMoveBack - moveBack ).LengthSq() > 0.00001f){

			btTransform btStart;
			btTransform btEnd;
			btStart.setIdentity();
			btEnd.setIdentity();
			btStart.setOrigin( ( nextPos + moveBack ).toBT() );
			btEnd.setOrigin( ( nextPos + normalMoveBack ).toBT() );

			//�R�[���o�b�N
			sweepResult2.me = m_rigidBody.GetBody();
			sweepResult2.m_collisionFilterGroup = m_rigidBody.GetBody()->getCollisionFlags();
			g_physics.ConvexSweepTest( (const btConvexShape*)m_collider.GetBody(), btStart, btEnd, sweepResult2 );
			hasHit = sweepResult2.hasHit();
		}

		//�ǂÂ����̈ړ��ł����������B
		//���̃|���S���̖@���ƁA�O�̃|���S���̖@�����Ȃ��p�x�����ȏ�Ȃ�n�����Ƃ݂Ȃ��B
		if( hasHit &&
			acosf(CVector3(sweepResult2.m_hitNormalWorld).Dot(hitNormal)) > CMath::DegToRad(10)){

			//�ڒn����p�ɖ@�����X�V
			hitNormal.Set( sweepResult2.m_hitNormalWorld );

			//����͏Փ˓_�Ŏ~�߂邾���Ȃ̂ŁA�����Ɉړ��ʂ����߂�B
			CVector3 addVec2 = normalMoveBack - moveBack;
			CVector3 move = addVec * sweepResult2.m_closestHitFraction;

			nextPos += moveBack + move;
		} else{
			nextPos += normalMoveBack;
		}

		//�ڒn����
		const float upDot = CVector3::Up().Dot( hitNormal );
		if( moveSpeed.y < 0.0f && acosf( upDot ) < CMath::DegToRad( 50 ) ){
			m_isJump = false;
			m_isOnGround = true;
			moveSpeed.y = 0;
		}
	}

	//�ړ��m��B
	//�|�W�V�����𑫌��ɖ߂��B
	m_position.Set( nextPos.x, nextPos.y - (m_radius + m_height / 2), nextPos.z );
	btRigidBody* btBody = m_rigidBody.GetBody();
	//���̂𓮂����B
	btBody->setActivationState( DISABLE_DEACTIVATION );
	btTransform& trans = btBody->getWorldTransform();
	//���̂̈ʒu���X�V�B
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

