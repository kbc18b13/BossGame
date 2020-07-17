#include "stdafx.h"
#include "JumpAtk.h"

namespace PlayerSpace{
JumpAtk::JumpAtk(){
	m_needStamina = 5;
}

void JumpAtk::SubStart( Actor * p ){
	bool isHeavy= g_pad->IsTrigger( enButtonRB2 );

	m_sword->SetDamage( isHeavy ? 20 : 10 );
	m_stamina->Consume( m_needStamina );

	if( isHeavy ){
		p->AddVelocity( CVector3(0,-1,0) * 300 );
		m_model->Play( int( Player::Anim::JumpAtkH ), 0.1f );
	} else{
		CVector3 front = { 0,0,1 };
		m_model->GetRot().Multiply( front );
		front.y = -1;
		p->AddVelocity( front * 300 );
		m_model->Play( int( Player::Anim::JumpAtkL ), 0.1f );
	}
}

void JumpAtk::Update( Actor * p ){
	//’n–Ê‚É‚Â‚¢‚½‚çI‚í‚è
	if( m_chara->IsOnGround() && !m_model->IsPlaying()){
		ActEnd( int( Player::Act::Walker ) );
	}
	if( m_sword->IsAttacking() ){
		m_chara->Excecute();
	}
}
void JumpAtk::End( Actor * p ){
	m_sword->AttackEnd();
}
}