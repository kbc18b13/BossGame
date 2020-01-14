#include "stdafx.h"
#include "Actor.h"
#include "Camera/PlayerCamera.h"

Actor::Actor( UINT maxHP, IStage * stage ) : m_maxHP( maxHP ), m_nowHP( maxHP ), m_stage(stage){}

Actor::~Actor() {}

bool Actor::Damage( UINT damage, float coolTime, Actor* source ) {
	if( m_damageCool <= 0.0f ){
		m_damageCool = coolTime;
		m_nowHP = std::max(m_nowHP - damage, 0u);

		if( m_nowHP == 0 && lockCamera){
			lockCamera->TurnLockOn(m_stage);
		}
		return true;
	}
	return false;
}
