#pragma once
#include "Act.h"

namespace TrollAct{

class ActIdle : public Act{
public:
	ActIdle();
	void Start( Troll* t ) override;
	void Continue( Troll* t ) override;
private:
	float m_timer = 0;
};

}