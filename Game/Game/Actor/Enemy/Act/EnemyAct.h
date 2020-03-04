#pragma once
#include "Actor/Act/Act.h"

namespace EnemySpace{

class EnemyAct : public Act{
public:
	EnemyAct();
	~EnemyAct();

	virtual void Init(SkinModelRender* model, CharaConEx* chara, Actor* target){
		SetSkinModelRender( model );
		SetCharaCon( chara );
		m_target = target;
	}

protected:
	Actor* m_target = nullptr;
};

}