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
	//最初の一回だけ実行
	if( first ){
		//ジャンプベクトル。ここにちょうどプレイヤー上に着地するように移動ベクトルを加える。
		const float jumpPower = 600;

		CVector3 motion = player( t )->GetPos() - chara( t ).GetPosition();
		plength = motion.Length();

		//滞空時間
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

	//ジャンプ後に着地したら5秒待って次へ
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