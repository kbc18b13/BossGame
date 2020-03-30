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

			//�@�m�͈͊O�͑ҋ@
			m_timer = 1.5;

		}else if( toP.LengthSq() < 60 * 60 ){

			//���\�߂��ɂ���ꍇ�͎a�邩�A�������B
			int r = Util::RandomInt( 0, 3 );
			if( r == 0 ){
				ActEnd( int( SkeletonEnemy::ActE::SideWalk ) );
			} else{
				ActEnd( int(SkeletonEnemy::ActE::Attack) );
			}

		} else{

			//�W�����v�؂茗���Ȃ�m���Ő؂�B
			if( toP.LengthSq() < pow2( 150 ) /*&& Util::RandomInt( 0, 1 ) == 0*/ ){
				ActEnd( int( SkeletonEnemy::ActE::JumpAttack ) );
			} else{

				//�@�m�͈͓��ŉ�����Βǂ��B
				ActEnd( int( SkeletonEnemy::ActE::Chase ) );
			}
		}
	}

	//������肱��������
	toP.y = 0;
	CVector3 front( 0, 0, 1 );
	m_model->GetRot().Multiply( front );
	m_model->AddRot( Util::LookRotSLerp( toP , front, 0.1f) );
	m_chara->Excecute();
}



}