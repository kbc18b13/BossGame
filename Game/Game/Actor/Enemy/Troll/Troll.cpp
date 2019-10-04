#include "stdafx.h"
#include "Troll.h"
#include "graphics/SkinModelRender.h"
#include "physics/CollisionAttr.h"
#include "Scene/Stage1.h"
#include "Actor/Player/Player.h"
#include "Act/ActAttack.h"
#include "Act/ActIdle.h"
#include "Act/ActStep.h"
#include "Act/ActChase.h"

Troll::Troll(Stage1* stage) :stage(stage) , Actor(1000) , m_font(L"Assets/font/font.spritefont"){

	{
		m_model = NewGO<SkinModelRender>(0);
		m_animClip[enAnimWalk].Load(L"Assets/animData/TestTroll_Walk.tka", true);
		m_animClip[enAnimAttack].Load(L"Assets/animData/TestTroll_Attack.tka", false);
		m_animClip[enAnimJumpUp].Load(L"Assets/animData/TestTroll_JumpUp.tka", false);
		m_animClip[enAnimJumpDown].Load(L"Assets/animData/TestTroll_JumpDown.tka", false);
		m_animClip[enAnimIdle].Load(L"Assets/animData/TestTroll_Idle.tka", true);
		m_model->Init(L"Assets/modelData/TestTroll.cmo", m_animClip, enAnimNum);
	}

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

void Troll::Start() {
	m_actionArray[enActAttack].reset(new ActAttack());
	m_actionArray[enActChase].reset(new ActChase(stage->GetPlayer()));
	m_actionArray[enActWait].reset(new ActIdle());
	m_actionArray[enActStep].reset(new ActStep(stage->GetPlayer()));
	m_activeAction = m_actionArray[enActWait].get();
	m_activeAction->Start();
}

void Troll::Update() {

	if (! m_activeAction->Continue(m_CharaCon, m_model)) {
		int i = Util::RandomInt(0, enActNum-1);
		m_activeAction = m_actionArray[i].get();
		m_activeAction->Start();
	}

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
