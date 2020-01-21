#include "stdafx.h"
#include "Damage.h"

namespace PlayerAct{

Damage::Damage(){}

Damage::~Damage(){}

void Damage::Start( Player * p ){
	sword( p ).SlashEnd();
	model( p ).Play( int(Player::Anim::Damage) , 0.2f);
}

void Damage::ChangeState( Player * p ){
	if( !model( p ).IsPlaying() ){
		ChangeAct( p, Player::Anim::Idle );
	}
}

void Damage::Update( Player * p ){
	chara( p ).Excecute();
}

}