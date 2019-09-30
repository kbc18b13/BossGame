#pragma once
#include "Attack.h"

class DamageManager {
public:
	DamageManager();
	~DamageManager();

	bool TryAttack(Attack& atk);

	void Update();

private:

	std::vector<Attack> coolTimeList;
};
