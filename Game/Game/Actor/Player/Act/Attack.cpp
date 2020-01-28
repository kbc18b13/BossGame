#include "stdafx.h"
#include "Attack.h"

namespace PlayerSpace{

Attack::Attack( Player::Anim animation_, Player::Anim nextAttack_ ){
	animation = animation_;
	nextAttack = nextAttack_;
	m_needStamina = 5;
}


Attack::~Attack(){}

void Attack::SubStart( Actor* p ){
	m_sword->AttackStart();
	pushedAtkButton = false;
	m_timer = 0;
}

void Attack::Update( Actor* p ){
	//���
	if( g_pad->IsTrigger( enButtonB ) ){
		m_sword->AttackEnd();
		ActEnd( int(Player::Anim::Roll) );
		return;
	}

	//�U���{�^������������A���̑J�ڐ�̓R���{�U��
	if( g_pad->IsTrigger( enButtonRB1 ) ){
		pushedAtkButton = true;
	}

	//�R���{�\�Ȏ���
	if( m_timer > 0.3f ){
		if( nextAttack != Player::Anim::SlashEnd && pushedAtkButton ){
			
			if( m_stamina->Consume(m_needStamina) ){
				ActEnd( int( nextAttack ) );
				return;
			}
		}
	}

	//�A�j���[�V�����I����͑J��
	if( !m_model->IsPlaying() ){
		m_sword->AttackEnd();
		ActEnd( int(Player::Anim::Idle) );
		return;
	}

	m_model->Play( int( animation ), 0.2f );
	m_chara->Excecute();
	m_timer += GameTime::GetDeltaTime();
}

}