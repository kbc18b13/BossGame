#pragma once

class PlayerCamera;
class IStage;

class Actor : public IGameObject{
public:
	Actor(UINT maxHP, IStage* stage);
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

	//ステージをセット
	void SetStage( IStage* stage ){
		m_stage = stage;
	}

	//カメラでロックオン
	void LockOn( PlayerCamera* camera ){
		lockCamera = camera;
	}

	//ロックオン解除
	void UnLockOn(){
		lockCamera = nullptr;
	}

protected:
	float m_damageCool = 0.0f;
	UINT m_nowHP;
	UINT m_maxHP;
	PlayerCamera* lockCamera = nullptr;

	IStage* m_stage = nullptr;
};