#include "stdafx.h"
#include "SlimeAvoid.h"
#include "Actor/Actor.h"
#include "..\Slime.h"

namespace EnemySpace{

void SlimeAvoid::SubStart( Actor * a ){
	//“]‚ª‚é•ûŒü‚ÌŒˆ’èB
	m_moveVec = m_target->GetPos() - a->GetPos();
	m_moveVec.Normalize();
	CQuaternion::CreateRotDeg( -CVector3::AxisY(), 45 ).Multiply(m_moveVec);

	m_model->Play( int( Slime::Anim::Avoid ) );
}

void SlimeAvoid::Update( Actor * a ){
	m_chara->Excecute( m_moveVec, 2, 4, false );
	if( !m_model->IsPlaying() ){
		ActEnd( int( Slime::ActE::Idle ) );
	}
}

}