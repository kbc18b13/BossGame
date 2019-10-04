#pragma once
#include "Act.h"
#include "graphics/CFont.h"
class Player;

class ActStep : public Act {
public:
	ActStep(Player* player);

	void Start() override;
	bool Continue(CharaConEx& chara, SkinModelRender* model);

private:
	bool first = true;
	bool onJump = false;
	Player* player;

	CFont font;
};