#include "stdafx.h"
#include "Troll.h"
#include "graphics/SkinModelRender.h"
#include "physics/CollisionAttr.h"

Troll::Troll() : Actor(1000) , m_font(L"Assets/font/font.spritefont"){

	m_model = NewGO<SkinModelRender>(0);
	m_animClip[enAnimWalk].Load(L"Assets/animData/TestTroll_Attack.tka", true);
	m_model->Init(L"Assets/modelData/TestTroll.cmo", m_animClip, enAnimNum);

	m_CharaCon.Init(25 , 40, { 0,0,0 }, enCollisionAttr_Enemy, this);
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

void Troll::Draw() {
	m_font.Begine();
	wchar_t str[10];
	swprintf(str, L"%d", m_nowHP);
	m_font.DrawStr(str);
	m_font.End();
}
