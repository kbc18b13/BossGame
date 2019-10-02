#include "stdafx.h"
#include "Troll.h"
#include "graphics/SkinModelRender.h"
#include "physics/CollisionAttr.h"

Troll::Troll() : Actor(1000) , m_font(L"Assets/font/font.spritefont"){

	m_model = NewGO<SkinModelRender>(0);
	m_animClip[enAnimWalk].Load(L"Assets/animData/TestTroll_Attack.tka", true);
	m_model->Init(L"Assets/modelData/TestTroll.cmo", m_animClip, enAnimNum);


	CharaConDesc desc;
	{
		desc.radius = 25;
		desc.height = 40;

		desc.position = CVector3(0, 0, 0);

		desc.walkAccel = 100;
		desc.walkAccelAir = 10;
		desc.walkBrake = 10;
		desc.walkMax = 150;

		desc.gravity = 900;
		desc.jumpPower = 500;

		desc.userIndex = enCollisionAttr_Enemy;
		desc.userPointer = this;
	}
	m_CharaCon.Init(desc);
}

Troll::~Troll() {
}

void Troll::Update() {
	CVector2 o;
	CVector3 pos = m_CharaCon.Excecute(o, false);
	m_model->SetPos(pos);
}

void Troll::SetPos(const CVector3 & pos) {
	m_CharaCon.SetPosition(pos);
	m_model->SetPos(pos);
}

void Troll::Draw() {
	m_font.Begine();
	wchar_t str[10];
	swprintf(str, L"%d", m_nowHP);
	m_font.DrawStr(str);
	m_font.End();
}
