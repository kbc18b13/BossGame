#include "stdafx.h"
#include "ActAttack.h"
#include "graphics/SkinModelRender.h"
#include "Actor/Player/Player.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;

ActAttack::ActAttack(TrollArmCollision& arm) : m_arm(arm){
}

void ActAttack::Start() {
	m_timer = 1.5f;
    m_isAttack = false;
}

void ActAttack::Continue(ActArg& arg) {
	SkinModelRender* model = arg.model;
	CharaConEx* chara = arg.charaCon;

    CVector3 toP = arg.player->GetPos() - chara->GetPosition();

	model->Play(int(AnimState::Attack), 0.2f);
	model->SetPos(chara->Excecute(CVector3::Zero(), false));
    model->SetRot(Util::LookRotXZ(toP));

    if (!m_isAttack && m_timer < 1.0f) {
        m_arm.StartAttack();
        m_isAttack = true;
    }

	m_timer -= GameTime::GetDeltaTime();
    if (m_timer < 0) {
        m_arm.EndAttack();
        arg.changeAct(ActState::Wait);
    }
}
