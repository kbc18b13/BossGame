#pragma once
#include "Util/CharaConEx.h"
#include "graphics/SkinModelRender.h"
#include "Act/Act.h"

class PlayerCamera;
class IStage;

class Actor : public IGameObject{
public:
	Actor(UINT maxHP, IStage* stage);
	virtual ~Actor();

	void ActStateUpdate();

	void SetPos( const CVector3& pos ){
		m_chara.SetPosition( pos );
		m_model.SetPos( pos );
	}
	CVector3 GetPos() const{
		return m_chara.GetPosition();
	}

	void SetRot( const CQuaternion& pos ){
		m_model.SetRot( pos );
	}
	CQuaternion GetRot() const{
		return m_model.GetRot();
	}

	void AddVelocity( const CVector3& v ){
		m_chara.AddVelocity( v );
	}

	virtual bool Damage(UINT damage, Actor* source);

	UINT GetNowHP() const{
		return m_nowHP;
	}

	UINT GetMaxHP()  const{
		return m_maxHP;
	}

	float GetHPPer()  const{
		return float(m_nowHP) / m_maxHP;
	}

	float GetHeight() const{
		return m_chara.GetHeight();
	}

	bool IsDeath() const{
		return m_isDeath;
	}

	//ステージをセット
	void SetStage( IStage* stage ){
		m_stage = stage;
	}

	//ステージをゲット
	IStage* GetStage(){
		return m_stage;
	}

	//カメラでロックオン
	void LockOn( PlayerCamera* camera ){
		lockCamera = camera;
	}

	//ロックオン解除
	void UnLockOn(){
		lockCamera = nullptr;
	}

	virtual void SetStencilRef( int ref ){
		m_model.GetModel().SetStencilRef( ref );
	}

	float GetLockOnAngle(){
		return m_lockOnAngle;
	}

protected:
	void ChangeAct( int index ){
		m_nowAct->End( this );
		m_nowAct = GetAct( index );
		m_nowAct->Start( this );
	}

	virtual Act* GetAct( int index ) = 0;

	bool NowActIs( int index ){
		return m_nowAct == GetAct( index );
	}

	virtual void OnDeath(){};

	Act* m_nowAct = nullptr; //現在のステート

	UINT m_nowHP; //ヒットポイント
	UINT m_maxHP; //最大ヒットポイント
	PlayerCamera* lockCamera = nullptr;

	bool m_isDeath = false; //死亡していたらtrue

	IStage* m_stage = nullptr; //所属するステージ

	SkinModelRender m_model;
	CharaConEx m_chara;

	float m_lockOnAngle = 20; //このActorをロックオンした時の角度
};