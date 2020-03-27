#include "stdafx.h"
#include "Chase.h"
#include "Actor\Actor.h"
#include "Scene/IStage.h"

namespace EnemySpace{

Chase::Chase(int walkAnim, int nextState, float stopDistance ) :
	m_walkAnim(walkAnim), m_nextState(nextState), m_stopDistance(stopDistance){}

Chase::~Chase(){}

void Chase::SubStart( Actor* a ){
	m_timer = 5.0f;
}

void Chase::Update( Actor* a ){
	CVector3 toGO = a->GetStage()->GetShouldGo( a->GetPos(), m_target->GetPos() );

	CVector3 move = toGO - m_chara->GetPosition();
	move.y = 0;
	float moveLength = move.Length();
	if( moveLength < m_stopDistance ){
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