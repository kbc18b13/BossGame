#include "stdafx.h"
#include "Guard.h"
#include <vector>
namespace PlayerAct{

Guard::Guard(){}


Guard::~Guard(){}

void Guard::ChangeState( Player * p ){
	ChangeActDefault( p );
}

void Guard::Update( Player * p ){
	model( p ).Play( int( Player::Anim::Guard ) , 0.2f);
	CVector3 move = camera( p ).GetPadVec();
	chara( p ).Excecute(move, 0.3f, 1, false);
	if( move.LengthSq() > 0.01f ){
		rot( p ).SetRotationVec( CVector3::AxisZ(), move );
	}
}

}