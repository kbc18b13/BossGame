#pragma once
#include "Util/BarGauge.h"
class Stamina{
public:
	Stamina();
	~Stamina();

	void Update();
	bool Consume( float amount );

private:
	float m_maxStamina = 50;
	float m_stamina;
	BarGauge m_gauge;

	float m_recoverCool = 0;
};

