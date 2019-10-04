#include "stdafx.h"
#include "ActStep.h"
#include "Actor/Player/Player.h"
#include "graphics/SkinModelRender.h"



ActStep::ActStep(Player* player) : player(player), font(L"Assets/font/font.spritefont"){
	
}

void ActStep::Start(){
	onJump = false;
	first = true;
}

bool ActStep::Continue(CharaConEx & chara, SkinModelRender * model) {
	CVector3 pVec = player->GetPos() - chara.GetPosition();
	CVector3 sideVec;
	sideVec.Cross(pVec, CVector3::Up());

	sideVec.Normalize();

	model->SetPos( chara.Excecute(sideVec, first));

	first = false;

	if(!onJump){
		//�W�����v���ċ󒆂ɂ���
		if (!chara.OnGround()) {
			onJump = true;
		}
	} else {
		//�W�����v��ɐڒn������I��
		return !(chara.OnGround());
	}
	return true;
}
