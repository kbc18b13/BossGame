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
    //モデル
	{
		m_model = NewGO<SkinModelRender>(0);
		m_animClip[int(AnimState::Walk)].Load(L"Assets/animData/TestTroll_Walk.tka", true);
		m_animClip[int(AnimState::Attack)].Load(L"Assets/animData/TestTroll_Attack.tka", false);
		m_animClip[int(AnimState::JumpUp)].Load(L"Assets/animData/TestTroll_JumpUp.tka", false);
		m_animClip[int(AnimState::JumpDown)].Load(L"Assets/animData/TestTroll_JumpDown.tka", false);
		m_animClip[int(AnimState::Idle)].Load(L"Assets/animData/TestTroll_Idle.tka", true);
		m_model->Init(L"Assets/modelData/TestTroll.cmo", m_animClip, int(AnimState::Num));
	}

    //キャラコン
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

    //ステート変更関数
    m_stateChangeFunc = [&](ActState state) {
        m_activeAction = m_actionArray[int(state)].get();
        m_activeAction->Start();
    };
}

Troll::~Troll() {
}

void Troll::Start() {
	m_actionArray[int(ActState::Attack)].reset(new ActAttack());
	m_actionArray[int(ActState::Chase)].reset(new ActChase());
	m_actionArray[int(ActState::Wait)].reset(new ActIdle());
	m_actionArray[int(ActState::Step)].reset(new ActStep());
    m_stateChangeFunc(ActState::Wait);
}

void Troll::Update() {
	ActArg arg;
	arg.charaCon = &m_CharaCon;
	arg.model = m_model;
	arg.player = stage->GetPlayer();
    arg.changeAct = m_stateChangeFunc;
    m_activeAction->Continue(arg);
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
