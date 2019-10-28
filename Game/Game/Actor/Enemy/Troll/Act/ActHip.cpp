#include "stdafx.h"
#include "ActHip.h"
#include "graphics/SkinModelRender.h"
#include "Actor/Player/Player.h"
#include "Scene/Stage1.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;


ActHip::ActHip(){
	
}

void ActHip::Start(){
	onJump = false;
	first = true;
}

void ActHip::Continue(ActArg& arg) {
	CharaConEx* chara = arg.charaCon;

	CVector3 pVec = arg.player->GetPos() - chara->GetPosition();
	CVector3 sideVec;
	sideVec.Cross(pVec, CVector3::Up());

	sideVec.Normalize();

	arg.model->SetPos( chara->Excecute(sideVec, first));

	first = false;

	if(!onJump){
		//�W�����v���ċ󒆂ɂ���
		if (!chara->OnGround()) {
			onJump = true;
		}
	} else if(!chara->OnGround()){
		arg.changeAct(ActState::Wait);
	}
}
