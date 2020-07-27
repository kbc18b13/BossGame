#pragma once
#include "Ground/TriggerCollision.h"

class IStage;

class StageGate : public IGameObject{
public:
	StageGate();

	void Destroy();

	void Init( IStage* now, IStage* next, const CVector3& pos, const CQuaternion& rot );

	void SetAStage( IStage* stage ){
		m_AStage = stage;
	}

	void SetBStage( IStage* stage ){
		m_BStage = stage;
	}

	void Update();

private:
	void StencilUpdate();

	CVector3 m_pos;
	CVector3 m_toB;

	TriggerCollision m_col;
	SkinModelRender m_gateModel;
	SkinModelRender m_gateOutModel;

	IStage* m_AStage = nullptr;
	IStage* m_BStage = nullptr;
};

