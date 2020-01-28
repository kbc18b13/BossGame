#pragma once

class Player;

namespace EnemyAct{

class Chase : public Act{
public:
	ActChase();

	void Start(Troll* t) override;
	void Continue( Troll* t );

private:
	float m_timer = 0.0f;
};

}