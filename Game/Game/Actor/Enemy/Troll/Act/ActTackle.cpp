#include "stdafx.h"
#include "ActTackle.h"
#include "graphics/SkinModelRender.h"
#include "Actor/Player/Player.h"
#include "Scene/Stage1.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;


ActTackle::ActTackle(){
	
}

void ActTackle::Start(){
    m_timer = 5.0f;
}

void ActTackle::Continue(ActArg& arg) {

    CVector3 move = arg.player->GetPos() - arg.charaCon->GetPosition();
    move.y = 0;
    float moveLength = move.Length();
    if (moveLength < 100) {
        m_timer = 0;
    } else {
        move /= moveLength;
        move *= 2;
    }
    arg.model->Play(int(AnimState::Tackle), 0.2f);
    arg.model->SetPos(arg.charaCon->Excecute(move, false));
    arg.model->SetRot(Util::LookRotXZ(move));

    //タイマーが0を下回ったら終了
    if (m_timer <= 0) {
        arg.changeAct(ActState::Wait);
    }
}
