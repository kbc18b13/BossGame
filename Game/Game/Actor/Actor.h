#pragma once
#include "Util/CharaConEx.h"
#include "graphics/SkinModelRender.h"

class PlayerCamera;
class IStage;

class Actor : public IGameObject{
public:
	Actor(UINT maxHP, IStage* stage);
	virtual ~Actor();
    
    void Update() override{
		m_damageCool = std::max(m_damageCool - GameTime::GetDeltaTime(), 0.0f);
    }

	void SetPos( const CVector3& pos ){
		m_chara.SetPosition( pos );
		m_model.SetPos( pos );
	}
	CVector3 GetPos() const{
		return m_chara.GetPosition();
	}
	void AddVelocity( const CVector3& v ){
		m_chara.AddVelocity( v );
	}

	virtual bool Damage(UINT damage, Actor* source);

	UINT GetNowHP() {
		return m_nowHP;
	}

	UINT GetMaxHP() {
		return m_maxHP;
	}

	float GetHPPer() {
		return float(m_nowHP) / m_maxHP;
	}

	bool IsDeath(){
		return m_isDeath;
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
	float m_damageCool = 0.0f; //無敵時間
	UINT m_nowHP; //ヒットポイント
	UINT m_maxHP; //最大ヒットポイント
	PlayerCamera* lockCamera = nullptr;

	bool m_isDeath = false; //死亡していたらtrue

	IStage* m_stage = nullptr; //所属するステージ

	SkinModelRender m_model;
	CharaConEx m_chara;
};