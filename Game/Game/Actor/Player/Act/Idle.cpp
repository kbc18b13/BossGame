#include "stdafx.h"
#include "Idle.h"

namespace PlayerSpace{

Idle::Idle(){}

Idle::~Idle(){}

void Idle::Update(Actor* p ){
	if( g_pad->IsTrigger( enButtonB ) && m_stamina->CanDo()){
		ActEnd( int( Player::Anim::Roll ) );
		return;
	}

	if( g_pad->IsPress( enButtonLB1 ) ){
		ActEnd( int( Player::Anim::Guard ) );
		return;
	}

	if( g_pad->IsTrigger( enButtonRB1 ) && m_stamina->CanDo() ){
		ActEnd( int( Player::Anim::Slash1 ) );
		return;
	}

	if( g_pad->GetLStickVec().LengthSq() > 0.01f ){
		ActEnd( int( Player::Anim::Walk ) );
		return;
	}

	m_model->Play( int( Player::Anim::Idle ), 0.2f );
	m_chara->Excecute(CVector3::Zero(), g_pad->IsTrigger(enButtonA));
}

}
