#include "stdafx.h"
#include "ActHip.h"
#include "graphics/SkinModelRender.h"
#include "Actor/Player/Player.h"
#include "Scene/Stage1.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;

namespace TrollAct{

ActHip::ActHip(){

}

void ActHip::Start(){
	onJump = false;
	first = true;
}

void ActHip::Continue( ActArg& arg ){
	CharaConEx* chara = arg.charaCon;

	CVector3 motion;
	float plength = 0;
	//�ŏ��̈�񂾂����s
	if( first ){
		//�W�����v�x�N�g���B�����ɂ��傤�ǃv���C���[��ɒ��n����悤�Ɉړ��x�N�g����������B
		const float jumpPower = 600;

		CVector3 motion = arg.player->GetPos() - chara->GetPosition();
		plength = motion.Length();

		//�؋󎞊�
		float airTime = ( jumpPower / chara->GetGravity() * 2 );

		motion /= airTime;

		motion.y += jumpPower;

		chara->SetVelocity( motion );

		first = false;
	}

	if( chara->GetVelocity().y < 0 ){
		arg.model->Play( int( AnimState::Hip ), 0.2f );
	}

	arg.model->SetPos( chara->Excecute( CVector3::Zero(), false ) );

	//�W�����v��ɒ��n�����玟��
	if( !onJump ){
		if( !chara->OnGround() ){
			onJump = true;
		}
	} else if( chara->OnGround() ){
		arg.changeAct( ActState::Wait );
	}
}

}