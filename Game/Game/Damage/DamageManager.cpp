#include "stdafx.h"
#include "DamageManager.h"

DamageManager::DamageManager() {
}

DamageManager::~DamageManager() {
}

bool DamageManager::TryAttack(Attack& atk) {
	for (Attack& a : coolTimeList) {
		if (a.attackID == atk.attackID) {
			return false;
		}
	}

	coolTimeList.emplace_back(atk);
	return true;
}

void DamageManager::Update() {
	for (auto itr = coolTimeList.begin();  itr != coolTimeList.end();) {
		//クールタイムを減らして
		(*itr).coolTime -= GameTime::GetDeltaTime();

		//0以下なら削除
		if ((*itr).coolTime <= 0) {

			itr = coolTimeList.erase(itr);
		} else {

			itr++;
		}
	}
}
