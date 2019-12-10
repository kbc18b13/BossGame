#include "stdafx.h"
#include "Walk.h"

namespace PlayerAct{

Walk::Walk(){}


Walk::~Walk(){}

void Walk::ChangeState( ActArg & arg ){
	arg.changeActDefault();
}

void Walk::Update( ActArg& arg ){
	arg.model->Play( int( Player::Anim::Walk ), 0.2f );
	//ƒLƒƒƒ‰ƒRƒ“‚Ì‘€ì
	CVector3 move = g_pad->GetLStickXF() * arg.camera->GetRightVec()+
					g_pad->GetLStickYF() * arg.camera->GetFrontVec_XZ();
	arg.chara->Excecute( move, g_pad->IsTrigger( enButtonA ) );
}

}