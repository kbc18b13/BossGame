#include "stdafx.h"
#include "Roll.h"

namespace PlayerSpace{

Roll::Roll(){
	m_needStamina = 10;
}


Roll::~Roll(){}

void Roll::SubStart( Actor * p ){
	m_stamina->Consume( m_needStamina );

	//�ړ������̌���
	m_move = m_camera->GetPadVec();

	//�����͂̏ꍇ�͑O�ɁB
	if( m_move.LengthSq() < 0.01f ){
		m_move = CVector3( 0, 0, 1 );
		m_model->GetRot().Multiply( m_move );
	} else{
		//���͂��Ă�ꍇ�͂���������������B
		m_model->SetRot( Util::LookRotXZ( m_move ) );
	}
}

void Roll::Update( Actor * p ){
	m_model->Play( int( Player::Anim::Roll ) );
	m_chara->Excecute(m_move, 2, 2,false);

	//�A�j���[�V�����I�����B
	if( !m_model->IsPlaying() ){

		//�O�]�I�����ɒn�ʂɂ���Ύ~�܂�
		if( m_chara->OnGround() ){
			m_chara->SetVelocity( m_chara->GetVelocity() / 10 );
		}
		ActEnd( int( Player::Act::Walker ) );
	}
}

}