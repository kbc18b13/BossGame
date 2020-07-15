#pragma once
#include "Ground/TriggerCollision.h"

class IStage;

class StageGate : public IGameObject{
public:
	StageGate();
	~StageGate();

	void Init( IStage* now, IStage* next, const CVector3& pos );

	void SetNextStage( IStage* stage ){
		m_nextStage = stage;
	}

	void SetNowStage( IStage* stage ){
		m_nextStage = stage;
	}

	void Update();

private:
	CVector3 m_pos;
	CVector3 m_toNext;

	TriggerCollision m_col;
	SkinModelRender m_gateModel;

	IStage* m_nextStage = nullptr;
	IStage* m_NowStage = nullptr;
};

