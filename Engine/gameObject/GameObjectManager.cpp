#include "stdafx.h"
#include "GameObjectManager.h"
#include "IGameObject.h"


static GameObjectManager st_GoManager;

GameObjectManager::GameObjectManager() {
}


GameObjectManager::~GameObjectManager() {
}

void GameObjectManager::Init(UINT defArraySize, UINT defPrioSize) {
	m_goArray.resize(defPrioSize);
	for (UINT i = 0; i < defPrioSize; i++) {
		m_goArray[i].reserve(defArraySize);
	}
	m_newGOArray.resize(defPrioSize);
}

void GameObjectManager::Update() {
	{//新しいオブジェクトを追加
		UINT index = 0;
		for (std::vector<IGameObject*>& prioArray : m_newGOArray) {
			for (IGameObject* go : prioArray) {
				go->Start();
				m_goArray[index].push_back(go);
			}
			prioArray.clear();
			index++;
		}
	}

    //アップデート
	for (std::vector<IGameObject*>& prioArray : m_goArray) {
		for (IGameObject* go : prioArray) {
			if (!go->isRemoved) {
				go->Update();
			}
		}
	}

    //シャドウマップ書き込み
    g_graphicsEngine->GetShadowMap().RenderToShadowMap(g_graphicsEngine->GetD3DDeviceContext());

    //描画開始。
    g_graphicsEngine->BegineRender();

    //本描画
	for (std::vector<IGameObject*>& prioArray : m_goArray) {
		for (IGameObject* go : prioArray) {
			if (!go->isRemoved) {
				go->Draw();
			}
		}
	}

	for (std::vector<IGameObject*>& prioArray : m_goArray) {
		for (auto itr = prioArray.begin(); itr != prioArray.end();) {
			//ゲームオブジェクトを処分。
			if ((*itr)->isRemoved) {
				if((*itr)->needDelete)delete (*itr);//NewGOされたものはdeleteする。
				itr = prioArray.erase(itr);
			} else {
				itr++;
			}
		}
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
