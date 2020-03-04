#include "stdafx.h"
#include "SkeAttack.h"
#include "Actor/Player/Player.h"
#include "Actor/Enemy/Skeleton/SkeletonEnemy.h"

namespace EnemySpace{

SkeAttack::SkeAttack( ModelArmWeapon& sword, int animation, int maxCombo )
	: m_sword( sword ), m_anim( animation ), m_maxCombo( maxCombo ){}

SkeAttack::~SkeAttack(){}

void SkeAttack::SubStart( Actor* s ){
	m_nowCombo = 0;
	m_model->Play( m_anim, 0.1f);
	m_chara->Move( m_model->GetFront() * 50, 0.3f );
	//m_sword.AttackStart();
}

void SkeAttack::Update( Actor* s ){
	CVector3 toP = m_target->GetPos() - s->GetPos();

	if( !m_model->IsPlaying() ){
		m_sword.AttackEnd();
		m_nowCombo++;

		if( toP.LengthSq() < pow2( 40 ) && m_nowCombo < m_maxCombo ){
			m_model->Play( m_anim + m_nowCombo, 0.1f);
			m_chara->Move( m_model->GetFront() * 50, 0.3f );
		} else{
			ActEnd( int( SkeletonEnemy::Anim::Idle ) );
		}


	}

	toP.y = 0;
	CVector3 front( 0, 0, 1 );
	m_model->GetRot().Multiply( front );
	m_model->AddRot( Util::LookRotSLerp( toP, front, 0.1f ) );
	m_chara->Excecute();
}

void SkeAttack::End( Actor * s ){
	m_sword.AttackEnd();
}

}