#include "stdafx.h"
#include "ActChase.h"
#include "graphics/SkinModelRender.h"
#include "Actor/Player/Player.h"
#include "Scene/Stage1.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;

ActChase::ActChase(){
}

void ActChase::Start() {
	m_timer = 5.0f;
}

void ActChase::Continue(ActArg& arg) {
	
	CVector3 move = arg.player->GetPos() - arg.charaCon->GetPosition();
	move.y = 0;
	float moveLength = move.Length();
	if (moveLength < 100) {
		m_timer = 0;
	} else {
		move /= moveLength;
        move *= 0.11f;
	}
	arg.model->Play(int(AnimState::Walk), 0.2f);
	arg.model->SetPos(arg.charaCon->Excecute(move, false));
    arg.model->SetRot(Util::LookRotXZ(move));

	//タイマーが0を下回ったら終了
    if (m_timer <= 0) {
        arg.changeAct(ActState::Attack);
        return;
    }

    m_timer -= GameTime::GetDeltaTime();
}