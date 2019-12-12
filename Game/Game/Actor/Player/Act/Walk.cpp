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
	CVector3 move = g_pad->GetLStickXF() * camera( p ).GetRightVec() +
		g_pad->GetLStickYF() * camera( p ).GetFrontVec_XZ();
	chara( p ).Excecute( move, g_pad->IsTrigger( enButtonA ) );
}

}