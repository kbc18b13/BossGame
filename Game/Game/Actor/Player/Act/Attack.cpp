#include "stdafx.h"
#include "Attack.h"

namespace PlayerAct{

Attack::Attack( Player::Anim animation_, Act* nextAttack_ ){
	animation = animation_;
	nextAttack = nextAttack_;
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
		if( nextAttack && pushedAtkButton ){
			ChangeAct( p, nextAttack );
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