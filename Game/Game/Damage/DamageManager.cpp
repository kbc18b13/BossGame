#include "stdafx.h"
#include "DamageManager.h"

DamageManager::DamageManager() {
}

DamageManager::~DamageManager() {
}

bool DamageManager::TryAttack(Attack& atk) {
	for (CoolTimer& a : coolTimeList) {
		if (a.id == atk.attackID) {
			return false;
		}
	}

	coolTimeList.emplace_back(atk.attackID, atk.coolTime);
	return true;
}

void DamageManager::Update() {
	for (auto itr = coolTimeList.begin();  itr != coolTimeList.end();) {
		//�N�[���^�C�������炵��
		(*itr).time -= GameTime::GetDeltaTime();

		//0�ȉ��Ȃ�폜
		if ((*itr).time <= 0) {

			itr = coolTimeList.erase(itr);
		} else {

			itr++;
		}
	}
}
