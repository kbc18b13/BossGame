#pragma once
#include <functional>
#include "..\Player.h"

namespace PlayerAct{

class Act;

struct ActArg{
	std::function<void()> changeActDefault;
	std::function<void(Act*)> changeAct;
	SkinModelRender* model;
	CharaConEx* chara;
	PlayerCamera* camera;
};

class Act{
public:
	Act();
	virtual ~Act();

	virtual void ChangeState( ActArg& arg ) = 0;
	virtual void Update(ActArg& arg) = 0;

private:

};

}