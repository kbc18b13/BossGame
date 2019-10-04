#pragma once
#include "Act.h"
class ActIdle : public Act {
public:

	void Start() override;
	bool Continue(CharaConEx& chara, SkinModelRender* model) override;
private:
	float m_timer = 0;
};