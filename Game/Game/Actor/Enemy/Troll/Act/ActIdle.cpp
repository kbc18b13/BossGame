#include "stdafx.h"
#include "ActIdle.h"
#include "graphics/SkinModelRender.h"
#include "Actor/Player/Player.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;

namespace TrollAct{

ActIdle::ActIdle(){}

void ActIdle::Start(){
	m_timer = 1.0f;
}

void ActIdle::Continue( ActArg& arg ){
	arg.model->Play( int( AnimState::Idle ), 0.2f );
	m_timer -= GameTime::GetDeltaTime();
	arg.model->SetPos( arg.charaCon->Excecute( CVector3::Zero(), false ) );
	//�^�C�}�[��0���傫���Ԃ͑��s
	if( m_timer <= 0 ){
		CVector3 toP = arg.player->GetPos() - arg.charaCon->GetPosition();

		//�߂�
		if( toP.LengthSq() < 100 * 100 ){
			if( Util::RandomInt( 0, 3 ) == 0 ){
				arg.changeAct( ActState::Hip );
			} else{
				arg.changeAct( ActState::Attack );
			}

			//����
		} else{
			if( Util::RandomInt( 0, 3 ) == 0 ){
				arg.changeAct( ActState::Tackle );
			} else{
				arg.changeAct( ActState::Chase );
			}
		}
	}
}

}