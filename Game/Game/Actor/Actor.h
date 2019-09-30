#pragma once
class CVector3;
#include "Damage/DamageManager.h"

class Actor : public IGameObject{
public:
	Actor(UINT maxHP = 1);
	virtual ~Actor();

	virtual void SetPos(const CVector3& pos) = 0;
	virtual CVector3 GetPos() const = 0;

	virtual void Damage(Attack& atk);

	UINT GetNowHP() {
		return m_nowHP;
	}

	UINT GetMaxHP() {
		return m_maxHP;
	}

	float GetHPPer() {
		return float(m_nowHP) / m_maxHP;
	}

protected:
	DamageManager dmg;
	UINT m_nowHP;
	UINT m_maxHP;
};