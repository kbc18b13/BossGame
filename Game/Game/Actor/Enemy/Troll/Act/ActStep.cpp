#include "stdafx.h"
#include "ActStep.h"
#include "graphics/SkinModelRender.h"
#include "Actor/Player/Player.h"
#include "Scene/Stage1.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;


ActStep::ActStep() : font(L"Assets/font/font.spritefont"){
	
}

void ActStep::Start(){
	onJump = false;
	first = true;
}

void ActStep::Continue(ActArg& arg) {
	CharaConEx* chara = arg.charaCon;

	const CVector3 pVec = arg.player->GetPos() - chara->GetPosition();
	CVector3 sideVec;
	sideVec.Cross(pVec, CVector3::Up());

	sideVec.Normalize();

	arg.model->SetPos( chara->Excecute(sideVec, first));
    arg.model->SetRot(Util::LookRotXZ(pVec));

	first = false;

	if(!onJump){
		//ƒWƒƒƒ“ƒv‚µ‚Ä‹ó’†‚É‚¢‚é
		if (!chara->OnGround()) {
			onJump = true;
		}
	} else if(chara->OnGround()){
		arg.changeAct(pVec.Length());
	}
}
