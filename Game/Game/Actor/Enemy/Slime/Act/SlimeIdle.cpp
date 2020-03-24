#include "stdafx.h"
#include "SlimeIdle.h"
#include "Actor/Actor.h"
#include "..\Slime.h"

namespace EnemySpace{

SlimeIdle::SlimeIdle(){}
SlimeIdle::~SlimeIdle(){}

void SlimeIdle::SubStart( Actor * a ){
	m_timer = 0.3f;
	if( Util::RandomInt( 0, 5 ) == 0 ){
		CVector3 toP = m_target->GetPos() - a->GetPos();
		if( toP.LengthSq() < pow2( 200 ) ){
			ActEnd( int( Slime::ActE::Avoid ) );
		}
	}
	m_model->Play( int( Slime::Anim::Idle ), 0.3f );
}

void SlimeIdle::Update( Actor * a ){
	CVector3 toP = m_target->GetPos() - a->GetPos();

	if( m_timer > 0 || isActEnd()){
		m_timer -= GameTime::GetDeltaTime();
		return;
	}

	if( toP.LengthSq() > 300 * 300 ){

		//察知範囲外は待機
		m_timer = 1.5;

	} else if( toP.LengthSq() <60 * 60 ){
		//近ければ叩く
		ActEnd( int( Slime::ActE::Strike ) );
	} else{
		//遠ければ追う
		ActEnd( int( Slime::ActE::Chase ) );
	}
	m_chara->Excecute();
}

}