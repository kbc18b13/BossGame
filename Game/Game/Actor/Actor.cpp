#include "stdafx.h"
#include "Actor.h"
#include "Camera/PlayerCamera.h"

Actor::Actor( UINT maxHP, IStage * stage ) : m_maxHP( maxHP ), m_nowHP( maxHP ), m_stage( stage ){}

Actor::~Actor(){}

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
