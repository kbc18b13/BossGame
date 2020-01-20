#include "stdafx.h"
#include "ActIdle.h"
#include "graphics/SkinModelRender.h"
#include "Actor/Player/Player.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;

namespace TrollAct{

ActIdle::ActIdle(){}

void ActIdle::Start( Troll* t ){
	m_timer = 1.0f;
}

void ActIdle::Continue( Troll* t ){
	model( t ).Play( int( AnimState::Idle ), 0.2f );
	m_timer -= GameTime::GetDeltaTime();
	model( t ).SetPos( chara( t ).Excecute( CVector3::Zero(), false ) );

	CVector3 toP = player( t )->GetPos() - t->GetPos();

	//タイマーが0より大きい間は続行
	if( m_timer <= 0 && toP.LengthSq() < 500*500){
		ChangeActDefault( t );
	}
}

}