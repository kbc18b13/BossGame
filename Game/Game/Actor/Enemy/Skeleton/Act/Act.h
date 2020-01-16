#pragma once
#include "..\SkeletonEnemy.h"
#include "Scene/IStage.h"

namespace SkeletonAct{

class Act{
public:
	Act();
	virtual ~Act();

	virtual void Start( SkeletonEnemy* s );
	virtual void Update( SkeletonEnemy* s ) = 0;

protected:
	CharaConEx& chara( SkeletonEnemy* s ){
		return s->m_chara;
	}
	SkinModelRender& model( SkeletonEnemy* s ){
		return s->m_model;
	}
	Player* player( SkeletonEnemy* s ){
		return s->m_stage->GetPlayer();
	}
	Sword& sword( SkeletonEnemy* s ){
		return s->m_sword;
	}

	void ChangeAct( SkeletonEnemy* s, SkeletonEnemy::Anim state ){
		s->ChangeAct( state );
	}
};

}