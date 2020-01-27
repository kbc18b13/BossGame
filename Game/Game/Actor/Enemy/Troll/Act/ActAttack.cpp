#include "stdafx.h"
#include "ActAttack.h"
#include "graphics/SkinModelRender.h"
#include "Actor/Player/Player.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;

namespace TrollAct{

ActAttack::ActAttack( ArmWeapon& arm ) : m_arm( arm ){}

void ActAttack::Start( Troll* t ){
	m_timer = 1.5f;
	m_isAttack = false;
}

void ActAttack::Continue( Troll* t ){
	CVector3 toP = player( t )->GetPos() - chara( t ).GetPosition();

	model( t ).Play( int( AnimState::Attack ), 0.2f );
	model( t ).SetPos( chara( t ).Excecute( CVector3::Zero(), false ) );

	if( m_timer > 1.0f ){
		model( t ).SetRot( Util::LookRotXZ( toP ) );
	}

	if( !m_isAttack && m_timer < 1.0f ){
		m_arm.AttackStart();
		m_isAttack = true;
	}

	m_timer -= GameTime::GetDeltaTime();
	if( m_timer < 0 ){
		m_arm.AttackEnd();
		ChangeAct(t,  ActState::Wait );
	}
}

}