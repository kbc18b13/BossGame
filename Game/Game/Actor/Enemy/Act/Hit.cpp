#include "stdafx.h"
#include "Hit.h"
#include "Util/CharaConEx.h"

EnemySpace::Hit::Hit( int animation, int nextState ) : m_anim(animation), m_next(nextState){}

EnemySpace::Hit::~Hit(){}

void EnemySpace::Hit::SubStart( Actor * s ){
	m_model->Play( m_anim, 0.1f , true);
}

void EnemySpace::Hit::Update( Actor * s ){
	if( !m_model->IsPlaying() ){
		ActEnd( m_next );
	}
	m_chara->Excecute();
}
