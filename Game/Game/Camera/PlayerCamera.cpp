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

	//���C�L���X�g���g�����ǂɓ�����J����
	btCollisionWorld::ClosestRayResultCallback cb(look.toBT(), pos.toBT() );
	cb.m_collisionFilterMask = 0xffffffff;
	cb.m_collisionFilterMask ^= btCollisionObject::CollisionFlags::CF_Player;
	cb.m_collisionFilterGroup = btCollisionObject::CollisionFlags::CF_Camera;

	g_physics.GetDynamicWorld()->rayTest( look.toBT(), pos.toBT(), cb );

	if( cb.hasHit() ){
		//�Ⴊ�����������班���������ǂ��B
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

	//�G�̃��b�N�I��
	if( g_pad->IsTrigger( enButtonRB3 ) ){
		TurnLockOn();
	}

	{
		CVector3 playerPos = m_player->GetPos();
		playerPos.y += m_player->GetHeight();

		//�o�l�ʒu���v���C���[���ւ��炷
		m_springPPos.Lerp( 0.2f, m_springPPos, playerPos );

		//�v���C���[�ƃo�l�ʒu�ɍő勗����݂���
		CVector3 toSpring = m_springPPos - playerPos;
		if( toSpring.LengthSq() > pow2( 100 ) ){
			toSpring.Normalize();
			toSpring *= 100;
			m_springPPos = playerPos + toSpring;
		}
	}

	//���b�N�I�����̋���
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

		//�o�l��]
		m_springVec.Lerp( 0.7f, m_springVec, m_vec );

		//�J�����̍X�V�B
		UpdateGCamera( m_springPPos + m_springVec, m_springPPos );

		//�^�[�Q�b�g�摜�̈ړ�
		m_lockOnSprite.SetPosNormalized( g_camera3D.GetProjectedPos( ePos ).xy() );
		return;
	}

	//�񃍃b�N�I�����̋���

	//��荞�݃J����
	CVector3 PtoC = m_pos - m_springPPos;
	PtoC.Normalize();
	PtoC *= CtoPLength;

	//�ړ���̃x�N�g���ƑO��̃x�N�g���������By�͖����B
	m_vec.x = m_vec.x * 0.3f + PtoC.x * 0.7f;
	m_vec.z = m_vec.z * 0.3f + PtoC.z * 0.7f;

	//�c�����̉�]�͉��ɔ�ׂĒx������
	float yVec = m_vec.y * 0.7f + PtoC.y * 0.3f;

	//�c�����̉�]�́A���͈͓��Ɏ��܂��Ă��Ȃ���Ζ����ɂ���B
	constexpr float cos80 = 0.1736481f;
	constexpr float cos50 = 0.6427876f;
	if( cos80*CtoPLength < yVec && yVec < cos50*CtoPLength ){
		m_vec.y = yVec;
	}
	m_vec.Normalize();
	m_vec *= CtoPLength;
	
	//�X�e�B�b�N�ɂ���]�B
	CQuaternion rot;
	rot.SetRotationDeg( CVector3::AxisY(), g_pad->GetRStickXF() * ROT_SPEED * GameTime::GetDeltaTime() );
	rot.AddRotationDeg( GetRightVec(), -g_pad->GetRStickYF() * ROT_SPEED * GameTime::GetDeltaTime() );

	rot.Multiply( m_vec );

	//�㉺��]�ɐ�����������B
	float nowPitch = CMath::RadToDeg( acosf( CMath::Clamp( m_vec.y / CtoPLength, -1, 1) ));
	float clampPitch = nowPitch - CMath::Clamp( nowPitch, 90-LIMIT_UP_DOWN_ROT, 90+LIMIT_UP_DOWN_ROT );
	CQuaternion clampRot;
	clampRot.SetRotationDeg( GetRightVec(), clampPitch );

	clampRot.Multiply( m_vec );

	//�o�l��]
	m_springVec.Lerp( 0.7f, m_springVec, m_vec );

	//�|�W�V�����X�V
	m_pos = m_springPPos + m_vec;

	//�J�����̍X�V�B
	UpdateGCamera( m_springPPos + m_springVec, m_springPPos );
}

void PlayerCamera::LockOn(CVector2 pad ){
	float lockScore = std::numeric_limits<float>::max();
	Actor* lockOn = nullptr;

	//�X�N���[����̋����v�Z�̍ۂɒ��S�����炷���ƂŁA�p�b�h���͂Ń^�[�Q�b�g�؂�ւ����s����悤�ɂ���B
	if( pad.LengthSq() > pow2(0.01f) ){
		pad.Normalize();
		pad *= 0.4f;
	}

	for( Actor* e : m_player->GetStage()->GetEnemys() ){
		CVector3 ePos = e->GetPos();
		CVector3 pPos = m_pos - m_vec;

		//���S�҈ȊO�A���݃��b�N���ȊO
		if( !e->IsDeath()  && e != m_lockOnEnemy){

			//�X�N���[����ł̋���
			CVector4 toScreenCenter = g_camera3D.GetProjectedPos( ePos ) - CVector4(pad.x, pad.y, 0, 0);
			//�O������Ԃł̋���
			float toEnemy = ( ePos - pPos ).Length();

			//�������͈͓��̕�������Ώۂɂ���B
			if( toEnemy < TARGET_RANGE && toScreenCenter.xy().Length() < 0.8f && toScreenCenter.w > 0){

				float score = toScreenCenter.xy().Length() * 100 + toEnemy;
				//2D�A3D��̋�������Z�o�����X�R�A����ԏ��������̂�I�ԁB
				if( lockScore > score ){
					lockOn = e;
					lockScore = score;
				}
			}
		}
	}

	//���b�N�I���Ώۂ����݂����ꍇ
	if( lockOn ){
		//���ɉ��������b�N�I�����Ă������������B
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
