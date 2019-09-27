#include "stdafx.h"
#include "Sword.h"
#include "graphics/SkinModelRender.h"
#include "physics/CollisionAttr.h"

Sword::Sword(Bone* handBone) {
	m_model = NewGO<SkinModelRender>(3);
	m_model->Init(L"Assets/modelData/Sword.cmo");

	m_collider.Create({ 13,5,5 });
	m_collision.Create(m_collider);
	m_collision.SetGroup(1);
	m_collision.SetMask(0);
	g_physics.AddCollision(m_collision);
	
	m_hand = handBone;
}

Sword::~Sword() {
	DeleteGO(m_model);
}

void Sword::Update() {
	const CMatrix& worldMat = m_hand->GetWorldMatrix();

	CQuaternion rot;
	rot.SetRotation(worldMat);
	m_collision.GetBody()->getWorldTransform().setRotation(rot);

	CVector3 offset = m_offset;
	rot.Multiply(offset);
	CVector3 position = CVector3(worldMat.v[3]) + offset;
	m_collision.GetBody()->getWorldTransform().setOrigin(position);

	m_model->SetWorldMatrix(worldMat);
}
