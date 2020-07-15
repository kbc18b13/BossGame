#pragma once
#include "IStage.h"
#include "Ground/CollisionModel.h"

class Stage2 : public IStage{
public:
	Stage2();
	~Stage2();

	void Update();

private:
	CollisionModel ground;
};

