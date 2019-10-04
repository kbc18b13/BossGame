#include "stdafx.h"
#include "ActIdle.h"
#include "graphics/SkinModelRender.h"
#include "Util/CharaConEx.h"

void ActIdle::Start() {
	m_timer = 1.0f;
}

bool ActIdle::Continue(CharaConEx & chara, SkinModelRender * model) {
	model->Play(enAnimIdle, 0.2f);
	m_timer -= GameTime::GetDeltaTime();
	model->SetPos(chara.Excecute(CVector3::Zero(), false));
	//タイマーが0より大きい間は続行
	return m_timer > 0;
}