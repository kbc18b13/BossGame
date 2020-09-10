#include "stdafx.h"
#include "Actor.h"
#include "Camera/PlayerCamera.h"
#include "Scene/IStage.h"
#include "Actor/Player/Player.h"

Actor::Actor( UINT maxHP, IStage * stage ) : m_maxHP( maxHP ), m_nowHP( maxHP ), m_stage( stage ){}

Actor::~Actor(){}

void Actor::ActStateUpdate(){
	const float lensq = ( m_stage->GetPlayer()->GetPos() - GetPos() ).LengthSq();
	if( lensq > pow2( 1000 ) ){
		return;
	}

	m_nowAct->Update( this );
	if( m_nowAct->isActEnd() ){
		ChangeAct( m_nowAct->GetNextAct() );
	}
}

bool Actor::Damage( UINT damage, Actor* source ){
	m_nowHP = m_nowHP > damage ? m_nowHP - damage : 0;

	if( m_nowHP == 0 ){
		OnDeath();
		m_isDeath = true;
		if( lockCamera )
			lockCamera->ReLockOn();
	}
	return true;
}
