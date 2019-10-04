#pragma once
#include "Act.h"

class ActAttack : public Act {
public:
	void Start() override;
	bool Continue(CharaConEx& chara, SkinModelRender* model);

private:
	float m_timer = 0.0f;
};