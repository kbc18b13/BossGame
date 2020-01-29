#include "stdafx.h"
#include "Hit.h"

EnemySpace::Hit::Hit( int animation, int nextState ) : m_anim(animation), m_next(nextState){}

EnemySpace::Hit::~Hit(){}

void EnemySpace::Hit::SubStart( Actor * s ){
	m_model->Play( m_anim, 0.2f );
}

void EnemySpace::Hit::Update( Actor * s ){
	if( !m_model->IsPlaying() ){
		
	}
}
