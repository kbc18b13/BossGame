#include "stdafx.h"
#include "Walker.h"

namespace PlayerSpace{

Walker::Walker(){}

Walker::~Walker(){}

void Walker::Update(Actor* p ){
	if( g_pad->IsTrigger( enButtonB ) && m_stamina->CanDo()){
		ActEnd( int( Player::Act::Roll ) );
		return;
	}

	if( g_pad->IsPress( enButtonLB1 ) ){
		ActEnd( int( Player::Act::Guard ) );
		return;
	}

	if( (g_pad->IsTrigger( enButtonRB1 ) || g_pad->IsTrigger( enButtonRB2 ) )&& m_stamina->CanDo() ){
		ActEnd( int( Player::Act::Slash ) );
		return;
	}

	if( g_pad->GetLStickVec().LengthSq() > 0.01f ){
		//歩き
		m_model->Play( int( Player::Anim::Walk ), 0.2f);
		//キャラコンの操作
		CVector3 move = m_camera->GetPadVec();
		float speed = ( g_pad->IsPress( enButtonX ) && m_stamina->Consume( GameTime::GetDeltaTime() * 2 ) ) ? 1.5f : 1;

		m_chara->Excecute( move, speed, 1 / ( speed * 2 ), g_pad->IsTrigger( enButtonA ) );

		//モデルの向き
		m_model->SetRot( CQuaternion::CreateRotVec( CVector3::AxisZ(), move ) );
	} else{
		//何もしてない場合
		m_model->Play( int( Player::Anim::Idle ), 0.2f );
		m_chara->Excecute( CVector3::Zero(), g_pad->IsTrigger( enButtonA ) );
	}
}

}
