#pragma once
#include <functional>
#include "..\Player.h"

namespace PlayerAct{

class Act{
public:
	Act();
	virtual ~Act();

	virtual void Start( Player*);
	virtual void ChangeState(Player* p) = 0;
	virtual void Update(Player* p) = 0;

protected:
	PlayerCamera& camera( Player* p ){
		return p->m_camera;
	}
	SkinModelRender& model( Player* p ){
		return p->m_model;
	}
	CharaConEx& chara( Player* p ){
		return p->m_charaCon;
	}
	Sword& sword( Player* p ){
		return p->m_sword;
	}
	void ChangeActDefault( Player* p ){
		p->ChangeActDefault();
	}
	void ChangeAct(Player* p , Act* a){
		p->ChangeAct( a );
	}
};

}