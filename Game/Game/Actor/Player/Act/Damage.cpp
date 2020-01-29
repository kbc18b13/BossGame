#include "stdafx.h"
#include "Damage.h"

namespace PlayerSpace{

Damage::Damage(){}

Damage::~Damage(){}

void Damage::SubStart( Actor* p ){
	m_sword->AttackEnd();
	m_model->Play( int(Player::Anim::Damage) , 0.2f);
}

void Damage::Update( Actor* p ){
	m_chara->Excecute();
	if( !m_model->IsPlaying() ){
		ActEnd( int( Player::Act::Walker ) );
	}
}

}