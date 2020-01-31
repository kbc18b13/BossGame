#include "stdafx.h"
#include "..\Yowai.h"
#include "YowaIdle.h"
#include "Actor/Player/Player.h"

EnemySpace::YowaIdle::YowaIdle(){}

EnemySpace::YowaIdle::~YowaIdle(){}

void EnemySpace::YowaIdle::SubStart( Actor * s ){
	m_timer = 3;
	m_model->Play( int( Yowai::Anim::Idle ), 0.2f );
}

void EnemySpace::YowaIdle::Update( Actor * s ){
	m_chara->Excecute();

	if( m_timer > 0 ){
		m_timer -= GameTime::GetDeltaTime();
		return;
	}

	CVector3 toP = m_target->GetPos() - s->GetPos();

	//‰“‚¯‚ê‚Î‘Ò‚Â
	if( toP.LengthSq() < 300 * 300 ){

		//‹ß‚¯‚ê‚Î’@‚­‚©’Ç‚¤
		if( toP.LengthSq() < 40 * 40 ){
			ActEnd( int( Yowai::Anim::Attack ) );
		} else{
			ActEnd( int( Yowai::Anim::Walk ) );
		}
	}
}
