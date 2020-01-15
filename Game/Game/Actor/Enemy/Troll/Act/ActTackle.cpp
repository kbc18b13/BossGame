#include "stdafx.h"
#include "ActTackle.h"
#include "graphics/SkinModelRender.h"
#include "Actor/Player/Player.h"
#include "Scene/Stage1.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;

namespace TrollAct{

ActTackle::ActTackle( TrollBodyCollision& body ) : bodyCol( body ){

}

void ActTackle::Start( Troll* t ){
	bodyCol.StartAttack();
	playerPos = player( t )->GetPos();
	m_timer = 8.0f;
}

void ActTackle::Continue( Troll* t ){
	//プレイヤーへ向かって走らせる
	CVector3 move = playerPos - chara( t ).GetPosition();

	move.y = 0;
	float moveLength = move.Length();

	if(moveLength < 10 ){
		m_timer = 0;
	}

	move /= moveLength;
	move *= 5;

	model( t ).Play( int( AnimState::Tackle ), 0.2f );
	model( t ).SetPos( chara( t ).Excecute( move, 2, 1, false ) );
	model( t ).SetRot( Util::LookRotXZ( move ) );

	//タイマーが0を下回ったら終了
	if( m_timer <= 0 ){
		bodyCol.EndAttack();
		ChangeAct( t, ActState::Wait );
	} else{
		m_timer -= GameTime::GetDeltaTime();
	}
}

}
