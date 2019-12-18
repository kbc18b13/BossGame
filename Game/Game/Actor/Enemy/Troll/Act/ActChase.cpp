#include "stdafx.h"
#include "ActChase.h"
#include "graphics/SkinModelRender.h"
#include "Actor/Player/Player.h"
#include "Scene/Stage1.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;

namespace TrollAct{

ActChase::ActChase(){}

void ActChase::Start( Troll* t ){
	m_timer = 5.0f;
}

void ActChase::Continue( Troll* t ){

	CVector3 move = player( t )->GetPos() - chara( t ).GetPosition();
	move.y = 0;
	float moveLength = move.Length();
	if( moveLength < 100 ){
		m_timer = 0;
	} else{
		move /= moveLength;
		move *= 0.11f;
	}
	model( t ).Play( int( AnimState::Walk ), 0.2f );
	model( t ).SetPos( chara( t ).Excecute( move, false ) );
	model( t ).SetRot( Util::LookRotXZ( move ) );

	//タイマーが0を下回ったら終了
	if( m_timer <= 0 ){
		ChangeAct( t, ActState::Attack );
		return;
	}

	m_timer -= GameTime::GetDeltaTime();
}

}