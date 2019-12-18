#include "stdafx.h"
#include "ActIdle.h"
#include "graphics/SkinModelRender.h"
#include "Actor/Player/Player.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;

namespace TrollAct{

ActIdle::ActIdle(){}

void ActIdle::Start( Troll* t ){
	m_timer = 1.0f;
}

void ActIdle::Continue( Troll* t ){
	model( t ).Play( int( AnimState::Idle ), 0.2f );
	m_timer -= GameTime::GetDeltaTime();
	model( t ).SetPos( chara( t ).Excecute( CVector3::Zero(), false ) );
	//�^�C�}�[��0���傫���Ԃ͑��s
	if( m_timer <= 0 ){
		CVector3 toP = player( t )->GetPos() - chara( t ).GetPosition();

		//�߂�
		if( toP.LengthSq() < 100 * 100 ){
			if( Util::RandomInt( 0, 3 ) == 0 ){
				ChangeAct( t, ActState::Hip );
			} else{
				ChangeAct( t, ActState::Attack );
			}

			//����
		} else{
			if( Util::RandomInt( 0, 3 ) == 0 ){
				ChangeAct( t, ActState::Tackle );
			} else{
				ChangeAct( t, ActState::Chase );
			}
		}
	}
}

}