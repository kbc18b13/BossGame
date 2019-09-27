#pragma once
#include "ICollision.h"

class ICollider;

class GhostObject : public ICollision{
public:
	GhostObject();
	~GhostObject();

	void Create(const ICollider& collider, const CVector3 pos = CVector3(), const CQuaternion rot = CQuaternion());

	btGhostObject* GetBody() override{
		return &m_ghost;
	}

	void SetMask(short mask) {
		m_mask = mask;
	}

	void SetGroup(short group) {
		m_group = group;
	}

	short GetMask() override {
		return m_mask;
	}

	short GetGroup() override {
		return m_group;
	}
private:
	btGhostObject m_ghost;
	short m_mask;
	short m_group;
};