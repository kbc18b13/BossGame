#include "stdafx.h"
#include "Troll.h"
#include "graphics/SkinModelRender.h"

Troll::Troll() {
	m_model = NewGO<SkinModelRender>(0);
	m_animClip[enAnimWalk].Load(L"Assets/animData/TestTroll_Crush.tka", true);
	m_model->Init(L"Assets/modelData/TestTroll.cmo", m_animClip, enAnimNum);
	m_model->SetPos({ 300,80,0 });
}

Troll::~Troll() {
}

void Troll::Update() {
}

void Troll::SetPos(const CVector3 & pos) {
	m_model->SetPos(pos);
}
