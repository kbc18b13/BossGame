#include "stdafx.h"
#include "Ground1.h"

Ground::Ground() {
	m_model.Init(L"Assets/modelData/TestStage.cmo");
	m_collider.CreateMeshObject(m_model.GetModel(), {0,0,0}, CQuaternion::Identity());
}

Ground::~Ground() {
}

void Ground::SetPos(const CVector3 & pos) {
	m_model.SetPos(pos);
	m_collider.SetPos(pos);
}
