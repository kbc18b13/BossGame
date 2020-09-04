#pragma once
#include "PlayerAct.h"
#include "util/LongPressButton.h"

namespace PlayerSpace{

class Attack : public PlayerAct{
public:
	Attack( Player::Anim animation1, int combo, SkinModelRender* model , LongPressButton* dash);
	~Attack();

	void SubStart( Actor* p ) override;

	void Update( Actor* p ) override;

	void End( Actor * p ) override;

private:
	int m_animation;
	const int m_maxCombo;

	enum class Atk{
		None,
		Light,
		Heavy,
	};
	Atk m_next = Atk::None;

	int m_nowCombo = 0;
	float m_timer = 0;

	bool m_canGoNext = false;

	void LocalStart( bool heavy);

	LongPressButton* m_dash;
};

}