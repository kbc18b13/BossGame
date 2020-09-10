#pragma once
#include "PlayerAct.h"

class Ladder;

namespace PlayerSpace{

class OnLadder : public PlayerAct{
public:
	OnLadder();
	~OnLadder();

	void SetLadder( Ladder& ladder ){
		m_ladder = &ladder;
	}

	void SubStart( Actor* p ) override;

	void Update( Actor* p ) override;

	void End( Actor * p ) override;

private:
	float gripTime = 0.0f;
	static constexpr float c_gripTime = 0.2f;

	enum State{
		Grip,
		Climb,
		GetOff,
	};
	State state = Grip;

	CQuaternion firstRot;
	CVector3 firstPos;

	CQuaternion toRot;
	CVector3 toPos;

	Ladder* m_ladder;
	bool oriru = false;

	bool isUp = true;
};

}

