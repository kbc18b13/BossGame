#include "stdafx.h"
#include "Attack.h"

namespace PlayerSpace{

Attack::Attack( Player::Anim animation_, int combo ) : m_maxCombo(combo){
	m_animation = int(animation_);
	m_needStamina = 5;
}


Attack::~Attack(){}

void Attack::SubStart( Actor* p ){
	m_sword->AttackStart();
	m_model->Play( int( m_animation ), 0.2f );
	m_pushedAtkButton = false;
	m_timer = 0;
	m_nowCombo = 1;
}

void Attack::Update( Actor* p ){
	//���
	if( g_pad->IsTrigger( enButtonB ) ){
		m_sword->AttackEnd();
		ActEnd( int(Player::Act::Roll) );
		return;
	}

	//�U���{�^������������A���̑J�ڐ�̓R���{�U��
	if( g_pad->IsTrigger( enButtonRB1 ) ){
		m_pushedAtkButton = true;
	}

	//�R���{�\�Ȏ���
	if( m_timer > 0.3f ){
		if( m_nowCombo < m_maxCombo && m_pushedAtkButton ){
			
			if( m_stamina->Consume(m_needStamina) ){
				m_sword->AttackStart();
				m_model->Play( int( m_animation + m_nowCombo ), 0.2f );
				m_pushedAtkButton = false;
				m_timer = 0;
				m_nowCombo++;
				return;
			}
		}

		//�K�[�h�ɂ��Ȃ���
		if( g_pad->IsPress( enButtonLB1 ) ){
			ActEnd( int( Player::Act::Guard ) );
			return;
		}
	}

	//�A�j���[�V�����I����͑J��
	if( !m_model->IsPlaying() ){
		m_sword->AttackEnd();
		ActEnd( int(Player::Act::Walker) );
		return;
	}
	m_chara->Excecute();
	m_timer += GameTime::GetDeltaTime();
}

}