#include "stdafx.h"
#include "Attack.h"

namespace PlayerSpace{

Attack::Attack( Player::Anim animation_, int combo, SkinModelRender* model ) : m_maxCombo( combo ){
	m_animation = int( animation_ );
	m_needStamina = 5;

	model->AddEventFunc( "Combo", [&](){
		m_canGoNext = true;
	} );
}


Attack::~Attack(){}

void Attack::LocalStart( bool heavy ){
	//m_sword->AttackStart() アニメーションイベントに移動。
	if( !heavy ){
		m_stamina->Consume( m_needStamina );
		m_sword->SetDamage( 1 );
		m_model->Play( int( m_animation + m_nowCombo ), 0.2f);
	} else{
		m_stamina->Consume( m_needStamina * 2);
		m_sword->SetDamage( 3 );
		m_model->Play( int( Player::Anim::HeavySlash ), 0.2f, true);
		m_nowCombo = 0;
	}

	m_next = Atk::None;
	m_timer = 0;
	m_canGoNext = false;
	m_nowCombo++;
	if( m_nowCombo == m_maxCombo ){
		m_nowCombo = 0;
	}
	m_chara->AddVelocity( m_model->GetFront() * 100 );
}

void Attack::SubStart( Actor* p ){
	m_nowCombo = 0;
	LocalStart( g_pad->IsTrigger( enButtonRB2 ) );
}

void Attack::Update( Actor* p ){
	//回避
	if( g_pad->IsTrigger( enButtonB ) ){
		ActEnd( int( Player::Act::Roll ) );
		return;
	}
	
	//コンボ入力確認
	if( m_next == Atk::None ){
		if( g_pad->IsTrigger( enButtonRB1 ) ){
			m_next = Atk::Light;
		} else if( g_pad->IsTrigger( enButtonRB2 ) ){
			m_next = Atk::Heavy;
		}
	}

	//コンボ可能な時間
	if( m_canGoNext || !m_model->IsPlaying()){
		if(m_next != Atk::None ){

			if( m_stamina->CanDo() ){
				LocalStart( m_next == Atk::Heavy );
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
		ActEnd( int( Player::Act::Walker ) );
		return;
	}
	m_chara->Excecute();
	m_timer += GameTime::GetDeltaTime();
}

void Attack::End( Actor * p ){
	m_sword->AttackEnd();
}

}