#pragma once
#include "Ground/TriggerCollision.h"
#include "Ground/GhostCollision.h"

class Player;
class IStage;

class StageGate : public IGameObject{
public:
	StageGate();

	void Destroy();

	void Init( IStage* now, IStage* next, Player* p ,const CVector3& pos, const CQuaternion& rot );

	void SetAStage( IStage* stage ){
		m_AStage = stage;
	}

	IStage* GetAStage()const{
		return m_AStage;
	}

	void SetBStage( IStage* stage ){
		m_BStage = stage;
	}

	IStage* GetBStage()const{
		return m_BStage;
	}

	void Update();

private:
	void StencilUpdate();
	void ShowA();
	void ShowB();

	Player* m_player;

	CVector3 m_pos;
	CVector3 m_toB;

	TriggerCollision m_col;
	SkinModelRender m_gateModel;
	SkinModelRender m_gateOutModel;

	IStage* m_AStage = nullptr;
	IStage* m_BStage = nullptr;
};

