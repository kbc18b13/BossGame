#pragma once
#include "character/CharacterController.h"

struct CharaConDesc {
	float radius = 0;
	float height = 0;

	CVector3 position;

	int userIndex     = enCollisionAttr_Character;
	void* userPointer = nullptr;

	float walkAccel    = 0;
	float walkAccelAir = 0;
	float walkBrake    = 0;
	float walkMax      = 0;

	float jumpPower    = 0;
	float gravity      = 0;
};

class CharaConEx {
public:
	void Init(const CharaConDesc& desc);

	CVector3 Excecute(const CVector3& moveXZ, bool jump);

	void SetPosition(const CVector3& pos) {
		m_charaCon.SetPosition(pos);
	}

	CVector3 GetPosition() const{
		return m_charaCon.GetPosition();
	}

	CVector3 GetVelocity() const {
		return CVector3(m_moveSpeedXZ.x, m_jumpSpeed, m_moveSpeedXZ.y);
	}

	bool OnGround() const {
		return m_charaCon.IsOnGround();
	}

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