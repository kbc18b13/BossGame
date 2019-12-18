#include "stdafx.h"
#include "Attack.h"

namespace PlayerAct{

Attack::Attack( Player::Anim animation_, Player::Anim nextAttack_ ){
	animation = animation_;
	nextAttack = nextAttack_;
	m_needStamina = 10;
}


Attack::~Attack(){}

void Attack::Start( Player* p ){
	sword( p ).SlashStart();
	pushedAtkButton = false;
}

void Attack::ChangeState( Player* p ){
	//�U���{�^������������A���̑J�ڐ�̓R���{�U��
	if( g_pad->IsTrigger( enButtonRB1 ) ){
		pushedAtkButton = true;
	}

	//�A�j���[�V�����I����ɂ����J�ڂ��Ȃ�
	if( !model( p ).IsPlaying() ){
		sword( p ).SlashEnd();
		if( nextAttack != Player::Anim::SlashEnd && pushedAtkButton && ChangeAct( p, nextAttack ) ){
			return;
		} else{
			ChangeActDefault( p );
		}
	}
}

void Attack::Update( Player* p ){
	model( p ).Play( int( animation ), 0.2f );
	chara( p ).Excecute();
}

}