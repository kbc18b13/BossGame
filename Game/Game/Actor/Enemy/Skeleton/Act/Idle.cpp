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

			//�����ɂ���Ƃ��͑ҋ@
			m_timer = 1.5;

		}else if( toP.LengthSq() < 40 * 40 ){

			//���\�߂��ɂ���ꍇ�͎a��B2��ނ��烉���_���ŁB
			if( Util::RandomInt( 0, 1 ) == 0 ){
				ChangeAct( s, SkeletonEnemy::Anim::Attack1 );
			} else{
				ChangeAct( s, SkeletonEnemy::Anim::Attack2 );
			}

		} else{

			//�߂����Ȃ����ǉ������Ȃ���Βǂ��B
			ChangeAct( s, SkeletonEnemy::Anim::Chase );
		}
	}

	//������肱��������
	toP.y = 0;
	CVector3 front( 0, 0, 1 );
	model( s ).GetRot().Multiply( front );
	model( s ).AddRot( Util::LookRotSLerp( toP , front, 0.1f) );
	chara( s ).Excecute();
}



}