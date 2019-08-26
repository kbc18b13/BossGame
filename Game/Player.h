#pragma once
#include "character/CharacterController.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;

private:
	SkinModel m_model;									//スキンモデル。
};

