#include "stdafx.h"
#include "Walk.h"

namespace PlayerAct{

Walk::Walk(){}


Walk::~Walk(){}

void Walk::ChangeState( Player* p ){
	ChangeActDefault( p );
}

void Walk::Update( Player* p ){
	model( p ).Play( int( Player::Anim::Walk ), 0.2f );
	//ƒLƒƒƒ‰ƒRƒ“‚Ì‘€ì
	CVector3 move = camera( p ).GetPadVec();
	float speed = ( g_pad->IsPress( enButtonX ) && stamina( p ).Consume( GameTime::GetDeltaTime() * 2 )) ? 1.5f : 1;

	chara( p ).Excecute( move,speed, 1 /(speed*2) ,g_pad->IsTrigger( enButtonA ) );

	//ƒ‚ƒfƒ‹‚ÌŒü‚«
	if( move.LengthSq() > 0.01f){
		rot(p).SetRotationVec( CVector3::AxisZ(), move);
	}
}

}