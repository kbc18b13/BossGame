#pragma once
#include "IStage.h"
#include "Ground/CollisionModel.h"
#include "Ground/SkyBox.h"

class Stage2 : public IStage{
public:
	Stage2();
	~Stage2();

	void Update() override;

	void EndStage() override{}

	void SetStageStencilRef( int ref ) override;

private:
	SkyBox sky;
	CollisionModel ground;
};

