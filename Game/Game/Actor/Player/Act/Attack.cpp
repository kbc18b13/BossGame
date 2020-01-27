#include "stdafx.h"
#include "Attack.h"

namespace PlayerAct{

Attack::Attack( Player::Anim animation_, Player::Anim nextAttack_ ){
	animation = animation_;
	nextAttack = nextAttack_;
	m_needStamina = 5;
}


Attack::~Attack(){}

void Attack::Start( Player* p ){
	sword( p ).AttackStart();
	pushedAtkButton = false;
	m_timer = 0;
}

void Attack::ChangeState( Player* p ){
	//�U���{�^������������A���̑J�ڐ�̓R���{�U��
	if( g_pad->IsTrigger( enButtonRB1 ) ){
		pushedAtkButton = true;
	}

	//�R���{�\�Ȏ���
	if( m_timer > 0.3f ){
		if( nextAttack != Player::Anim::SlashEnd && pushedAtkButton ){
			if( ChangeAct( p, nextAttack ) ){
				return;
			}
		}
	}

	//�A�j���[�V�����I����͑J��
	if( !model( p ).IsPlaying() ){
		sword( p ).AttackEnd();
		ChangeActDefault( p );
	}
}

void Attack::Update( Player* p ){
	model( p ).Play( int( animation ), 0.2f );
	chara( p ).Excecute();
	m_timer += GameTime::GetDeltaTime();
}

}