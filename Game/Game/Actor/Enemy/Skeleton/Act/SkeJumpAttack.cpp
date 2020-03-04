#include "stdafx.h"
#include "SkeJumpAttack.h"
#include "Actor/Player/Player.h"
#include "Actor/Enemy/Skeleton/SkeletonEnemy.h"

namespace EnemySpace{

SkeJumpAttack::SkeJumpAttack( ModelArmWeapon& sword)
	: m_sword( sword ){}

SkeJumpAttack::~SkeJumpAttack(){}

void SkeJumpAttack::SubStart( Actor* s ){
	m_model->Play( int(SkeletonEnemy::Anim::JumpAttack), 0.2f );
}

void SkeJumpAttack::Update( Actor* s ){
	CVector3 toP = m_target->GetPos() - s->GetPos();

	if( !m_model->IsPlaying() ){
		ActEnd( int( SkeletonEnemy::Anim::Idle ) );
	}

	m_model->SetRot( Util::LookRotXZ(toP));
	m_chara->Excecute();
}

void SkeJumpAttack::End( Actor * s ){
	m_sword.AttackEnd();
}

void SkeJumpAttack::Init( SkinModelRender * model, CharaConEx * chara, Actor * target ){
	model->AddEventFunc( "Jump", [=](){
		CVector3 toP = m_target->GetPos() - chara->GetPosition();
		float toPLen = toP.Length();

		toP /= toPLen;

		toP *= 300;

		toP.y += 300;

		chara->AddVelocity( toP );
	} );
	EnemyAct::Init( model, chara, target );
}

}