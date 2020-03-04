#include "stdafx.h"
#include "TrollAttack.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;

namespace EnemySpace{

TrollAttack::TrollAttack( ArmWeapon& arm ) : m_arm( arm ){}

void TrollAttack::SubStart( Actor* t ){
	m_timer = 1.5f;
	m_isAttack = false;
}

void TrollAttack::Update( Actor* t ){
	CVector3 toP = m_target->GetPos() - m_chara->GetPosition();

	m_model->Play( int( AnimState::Attack ), 0.2f );
	m_model->SetPos( m_chara->Excecute( CVector3::Zero(), false ) );

	if( m_timer > 1.0f ){
		m_model->SetRot( Util::LookRotXZ( toP ) );
	}

	if( !m_isAttack && m_timer < 1.0f ){
		m_arm.AttackStart();
		m_isAttack = true;
	}

	m_timer -= GameTime::GetDeltaTime();
	if( m_timer < 0 ){
		m_arm.AttackEnd();
		ActEnd( int( ActState::Wait ) );
	}
}

}