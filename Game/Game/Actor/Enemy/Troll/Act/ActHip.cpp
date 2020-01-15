#include "stdafx.h"
#include "ActHip.h"
#include "graphics/SkinModelRender.h"
#include "Actor/Player/Player.h"
#include "Scene/Stage1.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;

namespace TrollAct{

ActHip::ActHip( TrollBodyCollision& col ) : bodyCol(col){}

void ActHip::Start( Troll* t ){

	onJump = false;
	first = true;
	waitTime = 2.0f;
}

void ActHip::Continue( Troll* t ){
	CVector3 motion;
	float plength = 0;
	//�ŏ��̈�񂾂����s
	if( first ){
		//�W�����v�x�N�g���B�����ɂ��傤�ǃv���C���[��ɒ��n����悤�Ɉړ��x�N�g����������B
		const float jumpPower = 600;

		CVector3 motion = player( t )->GetPos() - chara( t ).GetPosition();
		plength = motion.Length();

		//�؋󎞊�
		float airTime = ( jumpPower / chara( t ).GetGravity());

		motion /= airTime;

		motion.y += jumpPower;

		chara( t ).SetVelocity( motion );

		first = false;
	}

	if( chara( t ).GetVelocity().y < 0 ){
		bodyCol.StartAttack();
		model( t ).Play( int( AnimState::Hip ), 0.2f );
	}

	model( t ).SetPos( chara( t ).Excecute( CVector3::Zero(), false ) );

	//�W�����v��ɒ��n������5�b�҂��Ď���
	if( !onJump ){
		if( !chara( t ).OnGround() ){
			onJump = true;
		}
	} else if( chara( t ).OnGround() ){
		bodyCol.EndAttack();
		waitTime -= GameTime::GetDeltaTime();
		if( waitTime <= 0 ){
			ChangeAct( t, ActState::Wait );
		}
	}
}

}