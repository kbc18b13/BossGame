#pragma once
#include "Act.h"

namespace PlayerAct{

class Roll : public Act{
public:
	Roll();
	~Roll();

	void ChangeState( Player* p ) override;

	void Start( Player* p ) override;

	void Update( Player* p ) override;

private:
	CVector3 m_move;
};

}

