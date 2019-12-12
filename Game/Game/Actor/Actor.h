#pragma once
class CVector3;
#include "Damage/DamageManager.h"

class Actor : public IGameObject{
public:
	Actor(UINT maxHP = 1);
	virtual ~Actor();
    
    void Update() {
		m_damageCool = std::max(m_damageCool - GameTime::GetDeltaTime(), 0.0f);
    }

	virtual void SetPos(const CVector3& pos) = 0;
	virtual CVector3 GetPos() const = 0;
    virtual void AddVelocity(const CVector3& v) = 0;

	virtual bool Damage(UINT damage, float coolTime, Actor* source);

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
	float m_damageCool = 0.0f;
	UINT m_nowHP;
	UINT m_maxHP;
};