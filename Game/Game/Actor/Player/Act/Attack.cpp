#include "stdafx.h"
#include "Attack.h"

namespace PlayerAct{

Attack::Attack(){}


Attack::~Attack(){}

void Attack::ChangeState( ActArg & arg ){
	//アニメーション終了後にしか遷移しない
	if( !arg.model->IsPlaying() ){
		if( pushedAtkButton ){
			arg.changeAct( nextAttack );
		} else{
			arg.changeActDefault();
		}
	}
}

void Attack::Update( ActArg & arg ){
	arg.model->Play( int( animation ), 0.2f );
}

}