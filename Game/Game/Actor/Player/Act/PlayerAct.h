#pragma once
#include "..\Player.h"
#include "Actor/Act/Act.h"

namespace PlayerSpace{

class PlayerAct : public Act{
public:
	PlayerAct();
	~PlayerAct();

	void SubStart( Actor* a ) override;
	void Update( Actor* a ) = 0;
	void End( Actor* a ) override;

	void Init(SkinModelRender* model, CharaConEx* chara, ModelArmWeapon* sword,
			   PlayerCamera* camera, Stamina* stamina ){
		SetSkinModelRender( model );
		SetCharaCon( chara );
		m_sword = sword; m_camera = camera; m_stamina = stamina;
	}

public:
	UINT m_needStamina = 0;
	ModelArmWeapon* m_sword;
	PlayerCamera* m_camera;
	Stamina* m_stamina;
};

}