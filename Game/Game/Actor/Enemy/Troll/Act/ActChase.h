#pragma once
#include "Act.h"

class Player;

class ActChase : public Act {
public:
	ActChase(Player* player);

	void Start() override;
	bool Continue(CharaConEx& chara, SkinModelRender* model);

private:
	Player* player;
	float m_timer = 0.0f;
};