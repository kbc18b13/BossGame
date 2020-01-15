#include "stdafx.h"
#include "ActStep.h"
#include "graphics/SkinModelRender.h"
#include "Actor/Player/Player.h"
#include "Scene/Stage1.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;

namespace TrollAct{

ActStep::ActStep() : font( L"Assets/font/font.spritefont" ){

}

void ActStep::Start( Troll* t ){
	onJump = false;
	first = true;
}

void ActStep::Continue( Troll* t ){
	const CVector3 pVec = player( t )->GetPos() - chara( t ).GetPosition();
	CVector3 sideVec = CVector3::Cross( pVec, CVector3::Up() );

	sideVec.Normalize();

	model( t ).SetPos( chara( t ).Excecute() );
	model( t ).SetRot( Util::LookRotXZ( pVec ) );

	if( first ){
		sideVec *= 500;
		sideVec.y += 500;
		chara( t ).AddVelocity( sideVec );
	}

	first = false;

	if( !onJump ){
		//�W�����v���ċ󒆂ɂ���
		if( !chara( t ).OnGround() ){
			onJump = true;
		}
	} else if( chara( t ).OnGround() ){
		ChangeAct( t, ActState::Wait );
	}
}

}