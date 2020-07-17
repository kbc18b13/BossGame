#include "stdafx.h"
#include "Walker.h"

namespace PlayerSpace{

Walker::Walker(){}

Walker::~Walker(){}

void Walker::Update( Actor* p ){
	//���[�����O
	if( g_pad->IsTrigger( enButtonB ) && m_stamina->CanDo() ){
		ActEnd( int( Player::Act::Roll ) );
		return;
	}

	//�K�[�h
	if( g_pad->IsPress( enButtonLB1 ) ){
		ActEnd( int( Player::Act::Guard ) );
		return;
	}

	//�U��
	if( ( g_pad->IsTrigger( enButtonRB1 ) || g_pad->IsTrigger( enButtonRB2 ) ) && m_stamina->CanDo() ){
		if( m_chara->IsOnGround() ){
			ActEnd( int( Player::Act::Slash ) );
		} else{
			ActEnd( int( Player::Act::JumpAtk ) );
		}
		return;
	}

	//����
	if( g_pad->GetLStickVec().LengthSq() > 0.01f ){
		//�����A�j���[�V����
		if( m_chara->IsOnGround() ) m_model->Play( int( Player::Anim::Walk ), 0.2f );

		//�L�����R���̑���
		CVector3 move = m_camera->GetPadVec();
		float speed = ( g_pad->IsPress( enButtonX ) && m_stamina->Consume( GameTime::GetDeltaTime() * 2 ) ) ? 1.5f : 1;

		m_chara->Excecute( move, speed, 1 / ( speed * 2 ), g_pad->IsTrigger( enButtonA ) );

		//���f���̌���
		m_model->SetRot( CQuaternion::CreateRotVec( CVector3::AxisZ(), move ) );
	} else{
		//�������ĂȂ��ꍇ
		if( m_chara->IsOnGround() ) m_model->Play( int( Player::Anim::Idle ), 0.2f );

		m_chara->Excecute( CVector3::Zero(), g_pad->IsTrigger( enButtonA ) );
	}

	//�W�����v�A�j���[�V����
	if( g_pad->IsTrigger( enButtonA ) /*&& m_chara->IsOnGround()*/ ){
		m_model->Play( int( Player::Anim::Jump ), 0.1f );
	}
}

}
