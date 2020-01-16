#include "stdafx.h"
#include "Chase.h"
#include "Actor/Player/Player.h"

namespace SkeletonAct{

Chase::Chase(){}

Chase::~Chase(){}

void Chase::Start( SkeletonEnemy * s ){
	m_timer = 5;
	model( s ).Play( int( SkeletonEnemy::Anim::Chase ), 0.5f );
}

void Chase::Update( SkeletonEnemy * s ){
	CVector3 toP = player( s )->GetPos() - s->GetPos();
	toP.y = 0;

	m_timer -= GameTime::GetDeltaTime();

	if( toP.LengthSq() < 40 * 40){
		if( Util::RandomInt( 0, 1 ) == 0 ){
			ChangeAct( s, SkeletonEnemy::Anim::Attack1 );
		} else{
			ChangeAct( s, SkeletonEnemy::Anim::Attack2 );
		}
	}else if( m_timer <= 0 ){
		ChangeAct( s, SkeletonEnemy::Anim::Idle );
	}

	toP.Normalize();

	chara( s ).Excecute( toP, false );

	//‚ä‚Á‚­‚è‚±‚Á‚¿Œü‚­
	toP.y = 0;
	CVector3 front( 0, 0, 1 );
	model( s ).GetRot().Multiply( front );
	model( s ).AddRot( Util::LookRotSLerp( toP, front, 0.1f ) );
}

}