#include "stdafx.h"
#include "Idle.h"

namespace PlayerAct{

Idle::Idle(){}

Idle::~Idle(){}

void Idle::ChangeState( ActArg & arg ){
	arg.changeActDefault();
}

void Idle::Update( ActArg & arg ){
	arg.model->Play( int( Player::Anim::Idle ), 0.2f );
}

}
