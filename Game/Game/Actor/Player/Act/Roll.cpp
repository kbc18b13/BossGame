#include "stdafx.h"
#include "Roll.h"

namespace PlayerSpace{

Roll::Roll(){
	m_needStamina = 10;
}


Roll::~Roll(){}

void Roll::SubStart( Actor * p ){
	m_stamina->Consume( m_needStamina );

	//移動方向の決定
	m_move = m_camera->GetPadVec();

	//未入力の場合は前に。
	if( m_move.LengthSq() < 0.01f ){
		m_move = CVector3( 0, 0, 1 );
		m_model->GetRot().Multiply( m_move );
	} else{
		//入力してる場合はそっちを向かせる。
		m_model->SetRot( Util::LookRotXZ( m_move ) );
	}
}

void Roll::Update( Actor * p ){
	m_model->Play( int( Player::Anim::Roll ) );
	m_chara->Excecute(m_move, 2, 2,false);

	//アニメーション終了時。
	if( !m_model->IsPlaying() ){

		//前転終了時に地面にいれば止まる
		if( m_chara->OnGround() ){
			m_chara->SetVelocity( m_chara->GetVelocity() / 10 );
		}
		ActEnd( int( Player::Act::Walker ) );
	}
}

}