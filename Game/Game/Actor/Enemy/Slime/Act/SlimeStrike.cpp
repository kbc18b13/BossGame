#include "stdafx.h"
#include "SlimeStrike.h"
#include "Actor/Actor.h"
#include "..\Slime.h"

namespace EnemySpace{

void SlimeStrike::SubStart( Actor * a ){
	int r = Util::RandomInt( 0, 2 );
	if( r == 0 ){
		m_model->Play( int( Slime::Anim::HeavyStrike ) , 0.2f);
		m_weapon.SetDamage( 4 );
		m_weapon.SetKnockBack( { 0,200,500 } );
		return;
	}
	m_model->Play( int( Slime::Anim::Strike ), 0.2f );
	m_weapon.SetDamage( 1 );
	m_weapon.SetKnockBack( { 0, 20, 50 } );
}

void SlimeStrike::Update( Actor * a ){
	CVector3 toP = m_target->GetPos() - a->GetPos();
	toP.y = 0;
	CVector3 front( 0, 0, 1 );
	m_model->GetRot().Multiply( front );
	m_model->AddRot( Util::LookRotSLerp( toP, front, 0.1f ) );

	if( !m_model->IsPlaying() ){
		ActEnd( int( Slime::ActE::Idle ) );
	}
}

}