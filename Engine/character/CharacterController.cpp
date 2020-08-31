/*!
* @brief	�L�����N�^�̃R���W�����R���g���[���B
*/

#include "stdafx.h"
#include "character/CharacterController.h"

using bcw = btCollisionWorld;

//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g
struct SweepResult : public bcw::ClosestConvexResultCallback{
	const btCollisionObject* me = nullptr;		//�������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o�B

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
	//�R���W�����쐬�B
	m_radius = radius;
	m_height = height;
	m_collider.Create( radius, height );

	//���̂��������B
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_collider;
	rbInfo.mass = 0.0f;
	m_rigidBody.Create( rbInfo );
	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	//���̂̈ʒu���X�V�B�����̃|�W�V�����������ɂ���悤�ɒ�������B
	trans.setOrigin( btVector3( position.x, position.y + radius + height / 2, position.z ) );
	//@todo ���Ή��Btrans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
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
		//������ђ��ɂ���B
		m_isJump = true;
		m_isOnGround = false;
	}

	//���̈ړ���ƂȂ���W���v�Z����B
	//�J�v�Z���̒��S�̈ʒu�ōl����B
	CVector3 startPos( m_position.x, m_position.y + m_height * 0.5f + m_radius, m_position.z );
	CVector3 nextPos = startPos + moveSpeed * deltaTime;

	//���̃t���[���ł̐ڒn����
	bool frameOnGround = false;

	//�Փ˔���B
	for( int i = 0 ; i < 10; i++ ){

		//���������Ȃ������画�肹���I���B
		CVector3 addVec = nextPos - startPos;
		if( addVec.LengthSq() < 0.00001f ){
			break;
		}

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

		//������Ȃ�������I���B
		if( !sweepResult.hasHit() ){
			break;
		}

		//�ʂ̖@��
		CVector3 hitNormal( sweepResult.m_hitNormalWorld );

		//�ڒn�̔���B�ڐG�ʂ̖@���Ə���������p�x�ȓ��Ȃ�n�ʂƂ݂Ȃ��B
		if( !frameOnGround && acosf( hitNormal.Dot( CVector3::Up() ) ) < CMath::DegToRad( 45 ) ){
			m_isJump = false;
			m_isOnGround = true;
			frameOnGround = true;
			moveSpeed.y = 0;
		}

		//�߂荞�݂������߂�
		CVector3 moveBack = -addVec * ( 1 - sweepResult.m_closestHitFraction ); //�߂荞�݂Ԃ�̃x�N�g���̋t

		//�ړ��������������Ȃ痧���Ă��邾���Ƃ݂Ȃ��A�@�����e���s��Ȃ��B(��Ŏ��d�Ŋ������肵�Ȃ��B)
		if( IsOnGround() && acosf( addVec.GetNormalized().Dot( CVector3::Down() ) ) < CMath::DegToRad( 10 ) ){
			nextPos += moveBack;
			break;
		}

		CVector3 normalMoveBack = hitNormal * ( moveBack ).Dot( hitNormal );//�@���ɓ��e�B

		//2��ڂ̔���ō��̃|���S���ƐG��Ȃ��悤�ɖ@�������ɏ�����������B
		startPos = nextPos + moveBack + hitNormal*0.1f;
		nextPos = nextPos + normalMoveBack + hitNormal*0.1f;
	}

	//�ڒn���ĂȂ�����B
	if( !frameOnGround )m_isOnGround = false;

	//�ړ��m��B
	//�|�W�V�����𑫌��ɖ߂��B
	m_position.Set( nextPos.x, nextPos.y - ( m_radius + m_height / 2 ), nextPos.z );
	btRigidBody* btBody = m_rigidBody.GetBody();
	//���̂𓮂����B
	btBody->setActivationState( DISABLE_DEACTIVATION );
	btTransform& trans = btBody->getWorldTransform();
	//���̂̈ʒu���X�V�B
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

