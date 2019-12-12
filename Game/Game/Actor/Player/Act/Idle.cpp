#include "stdafx.h"
#include "Idle.h"

namespace PlayerAct{

Idle::Idle(){}

Idle::~Idle(){}

void Idle::ChangeState( Player* p ){
	ChangeActDefault( p );
}

void Idle::Update( Player* p ){
	model( p ).Play( int( Player::Anim::Idle ), 0.2f );
	chara( p ).Excecute(CVector3::Zero(), g_pad->IsTrigger(enButtonA));
}

}
