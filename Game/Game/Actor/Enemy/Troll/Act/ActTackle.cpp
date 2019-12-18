#include "stdafx.h"
#include "ActTackle.h"
#include "graphics/SkinModelRender.h"
#include "Actor/Player/Player.h"
#include "Scene/Stage1.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;

namespace TrollAct{

ActTackle::ActTackle(){

}

void ActTackle::Start( Troll* t ){
	m_timer = 5.0f;
}

void ActTackle::Continue( Troll* t ){

	CVector3 move = player( t )->GetPos() - chara( t ).GetPosition();
	move.y = 0;
	float moveLength = move.Length();
	if( moveLength < 100 ){
		m_timer = 0;
	} else{
		move /= moveLength;
		move *= 2;
	}
	model( t ).Play( int( AnimState::Tackle ), 0.2f );
	model( t ).SetPos( chara( t ).Excecute( move, 2, 1, false ) );
	model( t ).SetRot( Util::LookRotXZ( move ) );

	//タイマーが0を下回ったら終了
	if( m_timer <= 0 ){
		ChangeAct( t, ActState::Wait );
	}
}

}
