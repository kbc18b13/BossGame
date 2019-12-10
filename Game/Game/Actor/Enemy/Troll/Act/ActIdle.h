#pragma once
#include "Act.h"

namespace TrollAct{

class ActIdle : public Act{
public:
	ActIdle();
	void Start() override;
	void Continue( ActArg& arg ) override;
private:
	float m_timer = 0;
};

}