#include "stdafx.h"
#include "SkeIdle.h"
#include "Actor/Player/Player.h"

namespace EnemySpace{
	
SkeIdle::SkeIdle(){}

SkeIdle::~SkeIdle(){}

void SkeIdle::SubStart( Actor* s ){
	m_timer = 1.5f;
	m_model->Play( int( SkeletonEnemy::Anim::Idle ), 0.5f );
}

void SkeIdle::Update( Actor* s ){
	m_timer -= GameTime::GetDeltaTime();
	CVector3 toP =  m_target->GetPos() - s->GetPos();

	if( m_timer <= 0 ){
		if( toP.LengthSq() > 300 * 300 ){

			//�����ɂ���Ƃ��͑ҋ@
			m_timer = 1.5;

		}else if( toP.LengthSq() < 40 * 40 ){

			//���\�߂��ɂ���ꍇ�͎a��B2��ނ��烉���_���ŁB
			if( Util::RandomInt( 0, 1 ) == 0 ){
				ActEnd( int(SkeletonEnemy::Anim::Attack1) );
			} else{
				ActEnd( int(SkeletonEnemy::Anim::Attack2) );
			}

		} else{

			//�߂����Ȃ����ǉ������Ȃ���Βǂ��B
			ActEnd( int(SkeletonEnemy::Anim::Chase ));
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