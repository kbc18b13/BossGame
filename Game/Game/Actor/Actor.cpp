#include "stdafx.h"
#include "Actor.h"

Actor::Actor(UINT maxHP) : m_maxHP(maxHP) , m_nowHP(maxHP){}

Actor::~Actor() {}

bool Actor::Damage( UINT damage, float coolTime, Actor* source ) {
	if( m_damageCool <= 0.0f ){
		m_damageCool = coolTime;
		m_nowHP = std::max(m_nowHP - damage, 0u);
		return true;
	}
	return false;
}
