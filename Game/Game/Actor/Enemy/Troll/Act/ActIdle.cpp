#include "stdafx.h"
#include "ActIdle.h"
#include "graphics/SkinModelRender.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;

ActIdle::ActIdle(){
}

void ActIdle::Start() {
	m_timer = 1.0f;
}

void ActIdle::Continue(ActArg& arg) {
	arg.model->Play(int(AnimState::Idle), 0.2f);
	m_timer -= GameTime::GetDeltaTime();
	arg.model->SetPos(arg.charaCon->Excecute(CVector3::Zero(), false));
	//タイマーが0より大きい間は続行
    if (m_timer <= 0) {
        arg.changeAct(ActState::Chase);
    }
}