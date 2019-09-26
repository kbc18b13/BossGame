#include "stdafx.h"
#include "Troll.h"
#include "graphics/SkinModelRender.h"

Troll::Troll() {
	m_model = NewGO<SkinModelRender>(0);
	m_animClip[enAnimWalk].Load(L"Assets/animData/TestTroll_Crush.tka", true);
	m_model->Init(L"Assets/modelData/TestTroll.cmo", m_animClip, enAnimNum);

	m_CharaCon.Init(25 , 40, { 0,0,0 });
}

Troll::~Troll() {
}

void Troll::Update() {
}

void Troll::SetPos(const CVector3 & pos) {
	m_CharaCon.SetPosition(pos);
	m_model->SetPos(pos);
	CVector3 o;
	m_CharaCon.Execute(1,o);
}
