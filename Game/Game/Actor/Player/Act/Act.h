#pragma once
#include "..\Player.h"
#include "Actor/Act/Act.h"

namespace PlayerAct{

class PlayerAct : public Act{
public:
	PlayerAct();
	~PlayerAct();

	void SubStart( Actor* a ) override;
	void Update( Actor* a ) = 0;
	void End( Actor* a ) override;

	bool ConsumeStamina(Stamina& stamina){
		return stamina.Consume(m_needStamina);
	}

protected:
	UINT m_needStamina = 0;
	ModelArmWeapon* m_sword;
	PlayerCamera* m_camera;
};

}