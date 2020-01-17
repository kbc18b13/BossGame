#include "stdafx.h"
#include "Ground.h"

Ground::Ground( const wchar_t* modelPath ) {
	m_model.Init(modelPath);
	//m_collider.CreateMeshObject(m_model.GetModel(), {0,0,0}, CQuaternion::Identity());
	m_collider.CreateMeshObject( modelPath, { 0,0,0 }, CQuaternion::Identity() );
}

Ground::~Ground() {
}

void Ground::SetPos(const CVector3 & pos) {
	m_model.SetPos(pos);
	m_collider.SetPos(pos);
}
