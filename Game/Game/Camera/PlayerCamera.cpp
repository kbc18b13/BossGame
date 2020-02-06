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

	//���C�L���X�g���g�����ǂɓ�����J����
	btCollisionWorld::ClosestRayResultCallback cb(look, m_pos);

	g_physics.GetDynamicWorld()->rayTest( look, m_pos, cb );

	if( cb.hasHit() ){
		//�Ⴊ�����������班���������ǂ��B
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

	//�G�̃��b�N�I��
	if( g_pad->IsTrigger( enButtonRB3 ) ){
		TurnLockOn();
	}

	CVector3 playerPos = m_player->GetPos();
	playerPos.y += m_player->GetHeight();

	//���b�N�I�����̋���
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

		//�J�����̍X�V�B
		UpdateGCamera( playerPos );

		//�^�[�Q�b�g�摜�̈ړ�
		m_lockOnSprite.SetPosNormalized( g_camera3D.GetProjectedPos( ePos ).xy() );
		return;
	}

	//�񃍃b�N�I�����̋���

	//��荞�݃J����
	CVector3 PtoC = m_pos - playerPos;
	PtoC.y = 0;
	PtoC.Normalize();
	PtoC *= CtoPLength;
	//�ړ���̃x�N�g���ƑO��̃x�N�g���������By�͖����B
	float nowYRot = m_vec.y;
	m_vec = m_vec * 0.3f + PtoC * 0.7f;
	m_vec.y = nowYRot;
	
	//�X�e�B�b�N�ɂ���]�B�����͉���]�B
	CQuaternion rot = CQuaternion::CreateRotDeg( CVector3::AxisY(), g_pad->GetRStickXF() * ROT_SPEED * GameTime::GetDeltaTime() );
	rot.Multiply( m_vec );

	//�㉺��]��float�ŕێ����Đ�����������B
	m_upDownRot -= g_pad->GetRStickYF() * ROT_SPEED * GameTime::GetDeltaTime();
	m_upDownRot = CMath::Clamp( m_upDownRot, -LIMIT_UP_DOWN_ROT, LIMIT_UP_DOWN_ROT );
	rot.SetRotationDeg( GetRightVec(), m_upDownRot );
	CVector3 upDownRoteteVec = m_vec;
	rot.Multiply( upDownRoteteVec );

	//�|�W�V�����X�V
	m_pos = playerPos + upDownRoteteVec;

	//�J�����̍X�V�B
	UpdateGCamera( playerPos );
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
			CVector2 toScreenCenter = g_camera3D.GetProjectedPos( ePos ).xy() - pad;
			//�O������Ԃł̋���
			float toEnemy = ( ePos - pPos ).Length();

			//�������͈͓��̕�������Ώۂɂ���B
			if( toEnemy < TARGET_RANGE && toScreenCenter.Length() < 1.0f ){

				float score = toScreenCenter.Length() * 100 + toEnemy;
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
		if( m_lockOnEnemy ){
			m_lockOnEnemy->UnLockOn();
		}
		m_lockOnEnemy = lockOn;
		m_lockOnEnemy->LockOn( this );
		m_lockOnSprite.SetIsDraw( true );
	}
}

void PlayerCamera::TurnLockOn(){
	//���b�N�I������
	if( IsLockOn() ){
		m_lockOnEnemy->UnLockOn();
		m_lockOnEnemy = nullptr;
		m_lockOnSprite.SetIsDraw( false );
		return;
	}

	//���b�N�I��
	LockOn();
}

CVector3 PlayerCamera::GetPadVec(){
	return ( g_pad->GetLStickXF() * GetRightVec() + g_pad->GetLStickYF() * GetFrontVec_XZ() );
}
