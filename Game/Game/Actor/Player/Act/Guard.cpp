#include "stdafx.h"
#include "Guard.h"
#include <vector>
namespace PlayerSpace{

Guard::Guard(){}


Guard::~Guard(){}

void Guard::Update( Actor * p ){
	m_model->Play( int( Player::Anim::Guard ) , 0.2f);
	CVector3 move = m_camera->GetPadVec();
	m_chara->Excecute(move, 0.3f, 1, false);
	if( move.LengthSq() > 0.01f ){
		m_model->SetRot( CQuaternion::CreateRotVec( CVector3::AxisZ(), move ) );
	}
	if( !g_pad->IsPress( enButtonLB1 ) ){
		ActEnd( int( Player::Act::Walker ) );
	}
}

}