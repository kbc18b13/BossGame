#include "stdafx.h"
#include "Chase.h"
#include "Actor\Actor.h"

namespace EnemySpace{

Chase::Chase(int walkAnim, int nextState ) : m_walkAnim(walkAnim), m_nextState(nextState){}

Chase::~Chase(){}

void Chase::SubStart( Actor* a ){
	m_timer = 5.0f;
}

void Chase::Update( Actor* a ){

	CVector3 move = m_target->GetPos() - m_chara->GetPosition();
	move.y = 0;
	float moveLength = move.Length();
	if( moveLength < 30 ){
		m_timer = 0;
	} else{
		move /= moveLength;
		move *= 0.11f;
	}
	m_model->Play( m_walkAnim, 0.2f );
	m_model->SetPos( m_chara->Excecute( move, false ) );
	m_model->SetRot( Util::LookRotXZ( move ) );

	//タイマーが0を下回ったら終了
	if( m_timer <= 0 ){
		ActEnd( m_nextState );
		return;
	}

	m_timer -= GameTime::GetDeltaTime();
}

}