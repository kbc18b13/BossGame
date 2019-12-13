#include "stdafx.h"
#include "Roll.h"

namespace PlayerAct{

Roll::Roll(){}


Roll::~Roll(){}

void Roll::ChangeState( Player * p ){
	//アニメーション終了時。
	if( !model( p ).IsPlaying() ){

		//前転終了時に地面にいれば止まる
		if( chara( p ).OnGround() ){
			chara( p ).SetVelocity( chara( p ).GetVelocity() / 10 );
		}
		ChangeActDefault(p);
	}
}

void Roll::Start( Player * p ){

	//移動方向の決定
	m_move = camera( p ).GetPadVec();
	//未入力の場合は前に。
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