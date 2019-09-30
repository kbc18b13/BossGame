#include "stdafx.h"
#include "Actor.h"

Actor::Actor(UINT maxHP) : m_maxHP(maxHP) , m_nowHP(maxHP){}

Actor::~Actor() {}

void Actor::Damage(Attack& atk) {
	if (dmg.TryAttack(atk)) {

		if (m_nowHP < atk.damage) {
			m_nowHP = 0;
		} else {
			m_nowHP -= atk.damage;
		}
	}
}
