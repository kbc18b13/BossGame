#include "stdafx.h"
#include "SkeIdle.h"
#include "Actor/Player/Player.h"

namespace EnemySpace{
	
SkeIdle::SkeIdle(){}

SkeIdle::~SkeIdle(){}

void SkeIdle::SubStart( Actor* s ){
	m_timer = 0.3f;
	m_model->Play( int( SkeletonEnemy::Anim::Idle ), 0.5f );
}

void SkeIdle::Update( Actor* s ){
	m_timer -= GameTime::GetDeltaTime();
	CVector3 toP =  m_target->GetPos() - s->GetPos();

	if( m_timer <= 0 ){
		if( toP.LengthSq() > 400 * 400 ){

			//察知範囲外は待機
			m_timer = 1.5;

		}else if( toP.LengthSq() < 60 * 60 ){

			//結構近くにいる場合は斬るか、横歩き。
			int r = Util::RandomInt( 0, 3 );
			if( r == 0 ){
				ActEnd( int( SkeletonEnemy::ActE::SideWalk ) );
			} else{
				ActEnd( int(SkeletonEnemy::ActE::Attack) );
			}

		} else{

			//ジャンプ切り圏内なら確率で切る。
			if( toP.LengthSq() < pow2( 150 ) /*&& Util::RandomInt( 0, 1 ) == 0*/ ){
				ActEnd( int( SkeletonEnemy::ActE::JumpAttack ) );
			} else{

				//察知範囲内で遠ければ追う。
				ActEnd( int( SkeletonEnemy::ActE::Chase ) );
			}
		}
	}

	//ゆっくりこっち向く
	toP.y = 0;
	CVector3 front( 0, 0, 1 );
	m_model->GetRot().Multiply( front );
	m_model->AddRot( Util::LookRotSLerp( toP , front, 0.1f) );
	m_chara->Excecute();
}



}