#include "stdafx.h"
#include "GameObjectManager.h"
#include "IGameObject.h"


static GameObjectManager st_GoManager;

GameObjectManager::GameObjectManager() {
}


GameObjectManager::~GameObjectManager() {
}

void GameObjectManager::Init(UINT defArraySize, UINT defPrioSize) {
	st_GoManager.m_goArray.resize(defPrioSize);
	for (UINT i = 0; i < defPrioSize; i++) {
		st_GoManager.m_goArray.reserve(defArraySize);
	}
}

void GameObjectManager::Update() {
	for (std::vector<IGameObject*> prioArray : m_goArray) {
		for (IGameObject* go : prioArray) {
			if (!go->isStarted) {
				go->Start();
				go->isStarted = true;
			}
		}
	}

	for (std::vector<IGameObject*> prioArray : m_goArray) {
		for (IGameObject* go : prioArray) {
			if (!go->isRemoved && go->isStarted) {
				go->Update();
			}
		}
	}

	for (std::vector<IGameObject*> prioArray : m_goArray) {
		for (IGameObject* go : prioArray) {
			if (!go->isRemoved && go->isStarted) {
				go->Draw();
			}
		}
	}

	for (std::vector<IGameObject*> prioArray : m_goArray) {
		auto endItr = std::remove_if(prioArray.begin(), prioArray.end(), [](IGameObject* go)->bool {
			return go->isRemoved;
		});

		//delete‚Ì•K—v‚ª‚ ‚é‚à‚Ì‚¾‚¯delete
		for (auto itr = endItr; itr != prioArray.end(); itr++) {
			if ((*itr)->needDelete) {
				delete (*itr);
			}
		}

		prioArray.erase(endItr, prioArray.end());
	}
}

void GameObjectManager::DeleteGO(IGameObject * go) {
	go->isRemoved = true;
}

void InitGameObjectManager(UINT defaultArraySize, UINT defaultPrioSize) {
	st_GoManager.Init(defaultArraySize, defaultPrioSize);
}

GameObjectManager& GOManager() {
	return st_GoManager;
}
