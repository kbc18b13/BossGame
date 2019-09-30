#include "stdafx.h"
#include "stdafx.h"
#include "Attack.h"

UINT Attack::nextAttackID = 0;

Attack::Attack(UINT damage, float coolTime) : damage(damage), coolTime(coolTime) {
}

Attack::~Attack() {
}

void Attack::UpdateAttackID() {
	attackID = nextAttackID;
	nextAttackID++;
}
