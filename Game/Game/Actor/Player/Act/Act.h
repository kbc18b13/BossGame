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

	bool ConsumeStamina(Stamina& stamina){
		return stamina.Consume(m_needStamina);
	}

protected:
	UINT m_needStamina = 0;

	CQuaternion& rot( Player* p ){
		return p->rot;
	}

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
	bool ChangeAct(Player* p , Player::Anim a){
		return p->ChangeAct( a );
	}
};

}