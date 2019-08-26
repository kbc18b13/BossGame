#pragma once

class GameObjectManager;

class IGameObject {
public:
	IGameObject();
	~IGameObject();

	virtual void Start();
	virtual void Update();

	virtual void Draw();

private:
	friend GameObjectManager;
	bool isStarted = false;
	bool isRemoved = false;
	bool needDelete = false;
};

