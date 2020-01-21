#include "stdafx.h"
#include "Idle.h"
#include "Actor/Player/Player.h"

namespace SkeletonAct{
	
Idle::Idle(){}

Idle::~Idle(){}

void Idle::Start( SkeletonEnemy * s ){
	m_timer = 1.5f;
	model( s ).Play( int( SkeletonEnemy::Anim::Idle ), 0.5f );
}

void Idle::Update( SkeletonEnemy * s ){
	m_timer -= GameTime::GetDeltaTime();
	CVector3 toP =  player( s )->GetPos() - s->GetPos();

	if( m_timer <= 0 ){
		if( toP.LengthSq() > 300 * 300 ){

			//遠くにいるときは待機
			m_timer = 1.5;

		}else if( toP.LengthSq() < 40 * 40 ){

			//結構近くにいる場合は斬る。2種類からランダムで。
			if( Util::RandomInt( 0, 1 ) == 0 ){
				ChangeAct( s, SkeletonEnemy::Anim::Attack1 );
			} else{
				ChangeAct( s, SkeletonEnemy::Anim::Attack2 );
			}

		} else{

			//近くもないけど遠くもなければ追え。
			ChangeAct( s, SkeletonEnemy::Anim::Chase );
		}
	}

	//ゆっくりこっち向く
	toP.y = 0;
	CVector3 front( 0, 0, 1 );
	model( s ).GetRot().Multiply( front );
	model( s ).AddRot( Util::LookRotSLerp( toP , front, 0.1f) );
	chara( s ).Excecute();
}



}