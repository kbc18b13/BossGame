#include "stdafx.h"
#include "Ground1.h"
#include "graphics/SkinModelRender.h"

Ground::Ground() {
	m_model = NewGO<SkinModelRender>(0);
	m_model->Init(L"Assets/modelData/TestStage.cmo");
	m_collider.CreateMeshObject(m_model->GetModel(), {0,0,0}, CQuaternion::Identity());
}

Ground::~Ground() {
	DeleteGO(m_model);
}
