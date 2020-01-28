#include "stdafx.h"
#include "Walk.h"

namespace PlayerSpace{

Walk::Walk(){}


Walk::~Walk(){}

void Walk::Update( Actor* p ){
	m_model->Play( int( Player::Anim::Walk ), 0.2f );
	//ƒLƒƒƒ‰ƒRƒ“‚Ì‘€ì
	CVector3 move = m_camera->GetPadVec();
	float speed = ( g_pad->IsPress( enButtonX ) && m_stamina->Consume( GameTime::GetDeltaTime() * 2 )) ? 1.5f : 1;

	m_chara->Excecute( move,speed, 1 /(speed*2) ,g_pad->IsTrigger( enButtonA ) );

	//ƒ‚ƒfƒ‹‚ÌŒü‚«
	if( move.LengthSq() > 0.01f){
		m_model->SetRot( CQuaternion::CreateRotVec( CVector3::AxisZ(), move ) );
	} else{
		ActEnd( int(Player::Anim::Idle) );
	}
}

}