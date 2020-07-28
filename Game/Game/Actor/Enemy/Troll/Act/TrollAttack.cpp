#include "stdafx.h"
#include "TrollAttack.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;

namespace EnemySpace{

TrollAttack::TrollAttack( ArmWeapon& arm ) : m_arm( arm ){}

void TrollAttack::Init( SkinModelRender * model, CharaConEx * chara, Actor * target ){
	EnemyAct::Init( model, chara, target );
	model->AddEventFunc( "Attack", [&](){
		m_arm.AttackStart();
		m_isAttack = true;
	}, int(AnimState::Attack) );
}

void TrollAttack::SubStart( Actor* t ){
	m_isAttack = false;
}

void TrollAttack::Update( Actor* t ){
	CVector3 toP = m_target->GetPos() - m_chara->GetPosition();

	m_model->Play( int( AnimState::Attack ), 0.2f );
	m_model->SetPos( m_chara->Excecute( CVector3::Zero(), false ) );

	if( !m_isAttack ){
		m_model->SetRot( Util::LookRotXZ( toP ) );
	}

	if( !m_model->IsPlaying() ){
		m_arm.AttackEnd();
		ActEnd( int( ActState::Wait ) );
	}
}

}