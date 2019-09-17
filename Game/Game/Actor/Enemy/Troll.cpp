#include "stdafx.h"
#include "Troll.h"
#include "graphics/SkinModelRender.h"

Troll::Troll() {
	m_model = NewGO<SkinModelRender>(0);
	m_animClip[enAnimWalk].Load(L"Assets/animData/TestTroll_Walk.tka", true);
	m_model->Init(L"Assets/modelData/TestTroll.cmo", m_animClip, enAnimNum);
	m_model->Play(0, 0);
	m_model->SetPos({ 0,0,0 });
}

Troll::~Troll() {
}

void Troll::Update() {
}
