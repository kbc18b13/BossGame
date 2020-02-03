#include "stdafx.h"
#include "Attack.h"

namespace PlayerSpace{

Attack::Attack( Player::Anim animation_, int combo ) : m_maxCombo(combo){
	m_animation = int(animation_);
	m_needStamina = 5;
}


Attack::~Attack(){}

void Attack::LocalStart(){
	m_sword->AttackStart();
	m_model->Play( int( m_animation + m_nowCombo ), 0.2f );
	m_pushedAtkButton = false;
	m_timer = 0;
	m_nowCombo++;
	m_chara->AddVelocity( m_model->GetFront() * 100 );
}

void Attack::SubStart( Actor* p ){
	m_nowCombo = 0;
	LocalStart();
}

void Attack::Update( Actor* p ){
	//回避
	if( g_pad->IsTrigger( enButtonB ) ){
		ActEnd( int(Player::Act::Roll) );
		return;
	}

	//攻撃ボタンを押したら、次の遷移先はコンボ攻撃
	if( g_pad->IsTrigger( enButtonRB1 ) ){
		m_pushedAtkButton = true;
	}

	//コンボ可能な時間
	if( m_timer > 0.3f ){
		if( m_nowCombo < m_maxCombo && m_pushedAtkButton ){
			
			if( m_stamina->Consume(m_needStamina) ){
				LocalStart();
				return;
			}
		}

		//ガードにもつなげる
		if( g_pad->IsPress( enButtonLB1 ) ){
			ActEnd( int( Player::Act::Guard ) );
			return;
		}
	}

	//アニメーション終了後は遷移
	if( !m_model->IsPlaying() ){
		ActEnd( int(Player::Act::Walker) );
		return;
	}
	m_chara->Excecute();
	m_timer += GameTime::GetDeltaTime();
}

void Attack::End( Actor * p ){
	m_sword->AttackEnd();
}

}