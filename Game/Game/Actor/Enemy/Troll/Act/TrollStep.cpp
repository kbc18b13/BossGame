#include "stdafx.h"
#include "TrollStep.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;

namespace EnemySpace{

TrollStep::TrollStep(){

}

void TrollStep::SubStart( Actor* t ){
	onJump = false;
	first = true;
}

void TrollStep::Update( Actor* t ){
	const CVector3 pVec = m_target->GetPos() - m_chara->GetPosition();
	CVector3 sideVec = pVec.Cross( CVector3::Up() );

	sideVec.Normalize();

	m_model->SetPos( m_chara->Excecute() );
	m_model->SetRot( Util::LookRotXZ( pVec ) );

	if( first ){
		sideVec *= 500;
		sideVec.y += 500;
		m_chara->AddVelocity( sideVec );
	}

	first = false;

	if( !onJump ){
		//ƒWƒƒƒ“ƒv‚µ‚Ä‹ó’†‚É‚¢‚é
		if( !m_chara->OnGround() ){
			onJump = true;
		}
	} else if( m_chara->OnGround() ){
		ActEnd(int( ActState::Wait) );
	}
}

}