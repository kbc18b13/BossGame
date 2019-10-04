#include "stdafx.h"
#include "ActAttack.h"
#include "graphics/SkinModelRender.h"
#include "Util/CharaConEx.h"

void ActAttack::Start() {
	m_timer = 1.5f;
}

bool ActAttack::Continue(CharaConEx & chara, SkinModelRender * model) {

	model->Play(enAnimAttack, 0.2f);
	model->SetPos(chara.Excecute(CVector3::Zero(), false));

	m_timer -= GameTime::GetDeltaTime();
	return m_timer >= 0;
}
