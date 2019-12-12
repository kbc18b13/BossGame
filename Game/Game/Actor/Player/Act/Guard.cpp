#include "stdafx.h"
#include "Guard.h"

namespace PlayerAct{

Guard::Guard(){}


Guard::~Guard(){}

void Guard::ChangeState( Player * p ){
	ChangeActDefault( p );
}

void Guard::Update( Player * p ){
	model( p ).Play( int( Player::Anim::Guard ) , 0.2f);
	chara( p ).Excecute();
}

}