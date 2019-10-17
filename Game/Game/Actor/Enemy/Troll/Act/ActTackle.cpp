#include "stdafx.h"
#include "ActTackle.h"
#include "graphics/SkinModelRender.h"
#include "Actor/Player/Player.h"
#include "Scene/Stage1.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;


ActTackle::ActTackle(){
	
}

void ActTackle::Start(){
	onJump = false;
	first = true;
}

void ActTackle::Continue(ActArg& arg) {
	CharaConEx* chara = arg.charaCon;

	CVector3 pVec = arg.player->GetPos() - chara->GetPosition();
	CVector3 sideVec;
	sideVec.Cross(pVec, CVector3::Up());

	sideVec.Normalize();

	arg.model->SetPos( chara->Excecute(sideVec, first));

	first = false;

	if(!onJump){
		//ƒWƒƒƒ“ƒv‚µ‚Ä‹ó’†‚É‚¢‚é
		if (!chara->OnGround()) {
			onJump = true;
		}
	} else if(!chara->OnGround()){
		arg.changeAct(ActState::Wait);
	}
}
