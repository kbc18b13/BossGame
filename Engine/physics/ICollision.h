#pragma once

class btCollisionObject;

enum CollisionFlag {
    Zero,
    Ghost
};

class ICollision {
public:
	virtual ~ICollision() {};

	virtual short GetMask() = 0;
	virtual short GetGroup() = 0;

	virtual btCollisionObject* GetBody() = 0;
};