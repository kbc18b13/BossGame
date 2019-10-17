#include "stdafx.h"
#include "ActAttack.h"
#include "graphics/SkinModelRender.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;

ActAttack::ActAttack() {
}

void ActAttack::Start() {
	m_timer = 1.5f;
}

void ActAttack::Continue(ActArg& arg) {
	SkinModelRender* model = arg.model;
	CharaConEx* chara = arg.charaCon;

	model->Play(int(AnimState::Attack), 0.2f);
	model->SetPos(chara->Excecute(CVector3::Zero(), false));

	m_timer -= GameTime::GetDeltaTime();
    if (m_timer < 0) {
        arg.changeAct(ActState::Step);
    }
}
