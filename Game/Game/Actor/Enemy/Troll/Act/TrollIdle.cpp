#include "stdafx.h"
#include "TrollIdle.h"
#include "graphics/SkinModelRender.h"
#include "Actor/Player/Player.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;

namespace EnemySpace{

TrollIdle::TrollIdle(){}

void TrollIdle::SubStart( Actor* t ){
	m_timer = 1.0f;
}

void TrollIdle::Update( Actor* t ){
	m_model->Play( int( AnimState::Idle ), 0.2f );
	m_timer -= GameTime::GetDeltaTime();
	m_chara->Excecute( CVector3::Zero(), false );

	CVector3 toP = m_target->GetPos() - t->GetPos();

	//タイマーが0より大きい間は続行
	if( m_timer <= 0 && toP.LengthSq() < 500 * 500 ){
		if( Util::RandomInt( 0, 4 ) == 0 ){
			ActEnd( int( ActState::Step ) );
			return;
		}

		//近い
		if( toP.LengthSq() < 100 * 100 ){
			if( Util::RandomInt( 0, 2 ) == 0 ){
				ActEnd( int( ActState::Hip ) );
			} else{
				ActEnd( int( ActState::Attack ) );
			}

			//遠い
		} else{
			if( Util::RandomInt( 0, 2 ) == 0 ){
				ActEnd( int( ActState::Tackle ) );
			} else{
				ActEnd( int( ActState::Chase ) );
			}
		}
	}
}

}