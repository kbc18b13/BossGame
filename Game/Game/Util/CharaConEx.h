#pragma once
#include "character/CharacterController.h"

class CharaConEx {
public:
	CVector3 Excecute(const CVector2& moveXZ, bool jump);

private:
	float m_walkAccel;
	float m_walkAccelAir;
	float m_walkBrake;
	float m_walkMax;

	float m_jumpPower;
	float m_gravity;

	CVector2 m_moveSpeedXZ;
	float m_jumpSpeed = 0.0f;

	CharacterController m_charaCon;
};