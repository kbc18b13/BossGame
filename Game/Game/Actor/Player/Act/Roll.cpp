#include "stdafx.h"
#include "Roll.h"

namespace PlayerAct{

Roll::Roll(){}


Roll::~Roll(){}

void Roll::ChangeState( Player * p ){
	//�A�j���[�V�����I�����B
	if( !model( p ).IsPlaying() ){

		//�O�]�I�����ɒn�ʂɂ���Ύ~�܂�
		if( chara( p ).OnGround() ){
			chara( p ).SetVelocity( chara( p ).GetVelocity() / 10 );
		}
		ChangeActDefault(p);
	}
}

void Roll::Start( Player * p ){

	//�ړ������̌���
	m_move = camera( p ).GetPadVec();
	//�����͂̏ꍇ�͑O�ɁB
	if( m_move.LengthSq() < 0.01f ){
		m_move = CVector3( 0, 0, 1 );
		rot( p ).Multiply( m_move );
	}
}

void Roll::Update( Player * p ){
	model( p ).Play( int( Player::Anim::Roll ) );
	chara( p ).Excecute(m_move, 2, 1,false);
}

}