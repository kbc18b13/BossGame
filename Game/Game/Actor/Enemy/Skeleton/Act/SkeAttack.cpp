#include "stdafx.h"
#include "SkeAttack.h"
#include "Actor/Player/Player.h"
#include "Actor/Enemy/Skeleton/SkeletonEnemy.h"

namespace EnemySpace{

SkeAttack::SkeAttack( ModelArmWeapon& sword, int animation ) : m_sword( sword ), m_anim( animation ){}

SkeAttack::~SkeAttack(){}

void SkeAttack::SubStart( Actor* s ){

	m_model->Play( m_anim, 0.1f, true );
	//m_sword.AttackStart();
}

void SkeAttack::Update( Actor* s ){

	if( !m_model->IsPlaying() ){
		m_sword.AttackEnd();

		CVector3 toP = s->GetPos() - m_target->GetPos();

		ActEnd( int( SkeletonEnemy::Anim::Idle ) );

	}
	m_chara->Excecute();
}

void SkeAttack::Init( SkinModelRender * model, CharaConEx * chara, Actor * target ){
	model->AddEventFunc( "Attack", [&](){
		m_sword.AttackStart();
	} );
	EnemyAct::Init( model, chara, target );
}

}