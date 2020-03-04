#include "stdafx.h"
#include "YowaAttack.h"
#include "..\Yowai.h"

namespace EnemySpace{

YowaAttack::YowaAttack( ArmWeapon& weapon ) : m_weapon( weapon ){}

YowaAttack::~YowaAttack(){}

void YowaAttack::SubStart( Actor * s ){
	m_model->Play( int( Yowai::Anim::Attack ), 0.2f );
	//m_weapon.AttackStart();
}

void YowaAttack::Update( Actor * s ){
	m_chara->Excecute();
	m_model->SetRot( Util::LookRotXZ( m_target->GetPos() - s->GetPos() ) );

	if( !m_model->IsPlaying() ){
		ActEnd( int( Yowai::Anim::Idle ) );
	}
}

void YowaAttack::End( Actor * s ){
	m_weapon.AttackEnd();
}

void YowaAttack::Init( SkinModelRender * model, CharaConEx * chara, Actor * target ){
	model->AddEventFunc( "Attack", [&](){
		m_weapon.AttackStart();
	} );
	EnemyAct::Init( model, chara, target );
}

}