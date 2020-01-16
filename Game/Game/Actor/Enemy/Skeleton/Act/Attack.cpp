#include "stdafx.h"
#include "Attack.h"
#include "Actor/Player/Player.h"

namespace SkeletonAct{

Attack::Attack( SkeletonEnemy::Anim anim, SkeletonEnemy::Anim next )
	: m_anim( int( anim ) ), m_next( next ){}

Attack::~Attack(){}

void Attack::Start( SkeletonEnemy * s ){

	model( s ).Play( m_anim, 0.1f, true );
	sword( s ).SlashStart();
}

void Attack::Update( SkeletonEnemy * s ){
	if( !model( s ).IsPlaying() ){
		sword( s ).SlashEnd();

		CVector3 toP = s->GetPos() - player( s )->GetPos();

		ChangeAct( s, SkeletonEnemy::Anim::Idle );

	}
	chara( s ).Excecute();
}

}