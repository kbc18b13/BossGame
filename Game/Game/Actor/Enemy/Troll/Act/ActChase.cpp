#include "stdafx.h"
#include "ActChase.h"
#include "Actor/Player/Player.h"
#include "graphics/SkinModelRender.h"

ActChase::ActChase(Player* player) : player(player) {
}

void ActChase::Start() {
	m_timer = 5.0f;
}

bool ActChase::Continue(CharaConEx & chara, SkinModelRender * model) {
	
	CVector3 move = player->GetPos() - chara.GetPosition();
	move.y = 0;
	float moveLength = move.Length();
	if (moveLength < 100) {
		move = CVector3::Zero();
		m_timer = 0;
	} else {
		move /= moveLength;
	}
	model->Play(enAnimWalk, 0.2f);
	model->SetPos(chara.Excecute(move, false));

	//タイマーが0より大きい場合続行
	return m_timer > 0;
}