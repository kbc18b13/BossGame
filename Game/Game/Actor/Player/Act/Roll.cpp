#include "stdafx.h"
#include "Roll.h"

namespace PlayerAct{

Roll::Roll(){}


Roll::~Roll(){}

void Roll::ChangeState( Player * p ){
	if( !model( p ).IsPlaying() ){
		ChangeActDefault(p);
	}
}

void Roll::Start( Player * p ){
	CVector3 move = g_pad->GetLStickXF() * camera( p ).GetRightVec() +
		g_pad->GetLStickYF() * camera( p ).GetFrontVec_XZ();

	if( move.LengthSq() < 0.01f ){
		move = CVector3( 0, 0, 1 );
		rot( p ).Multiply( move );
	}

	move *= 200;

	chara( p ).AddVelocity( move );
}

void Roll::Update( Player * p ){
	model( p ).Play( int( Player::Anim::Roll ) );
	chara( p ).Excecute();
}

}