#pragma once

struct Attack {
public:
	Attack(UINT damage, float coolTime);
	~Attack();

	void UpdateAttackID();

	UINT attackID = 0;
	UINT damage;
	float coolTime;

private:
	static UINT nextAttackID;
};
