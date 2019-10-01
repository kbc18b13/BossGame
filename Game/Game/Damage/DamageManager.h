#pragma once
#include "Attack.h"

class DamageManager {
public:
	DamageManager();
	~DamageManager();

	bool TryAttack(Attack& atk);

	void Update();

private:
	struct CoolTimer {
		UINT id;
		float time;
		CoolTimer(UINT id, float time) : id(id), time(time){}
	};
	std::vector<CoolTimer> coolTimeList;
};
