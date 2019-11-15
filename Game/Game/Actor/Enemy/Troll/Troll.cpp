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
#include "Act/ActTackle.h"
#include "Act/ActHip.h"

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
    m_font.SetPos({500.0f, 500.0f});

    Bone* arm = m_model->GetModel().GetSkeleton().GetBone(3);
    armCollision.Init(this, arm);
}

Troll::~Troll() {
}

void Troll::Start() {
	m_actionArray[int(ActState::Attack)].reset(new ActAttack());
	m_actionArray[int(ActState::Chase)].reset(new ActChase());
	m_actionArray[int(ActState::Wait)].reset(new ActIdle());
	m_actionArray[int(ActState::Step)].reset(new ActStep());
    m_actionArray[int(ActState::Tackle)].reset(new ActTackle());
    m_actionArray[int(ActState::Hip)].reset(new ActHip());

    //ステート変更関数
    m_stateChangeFunc = [&](float toPLength) {
        int ran = Util::RandomInt(0, 6);

        if (ran == 0) {
            //確率でステップ
            m_activeAction = m_actionArray[int(ActState::Step)].get();

        } else if (ran == 1) {
            //確率で休む
            m_activeAction = m_actionArray[int(ActState::Wait)].get();

        }else{

            if (toPLength < 300.0f) {
                //近い時
                //ヒップドロップか攻撃
                if(ran == 3){
                    m_activeAction = m_actionArray[int(ActState::Hip)].get();
                } else {
                    m_activeAction = m_actionArray[int(ActState::Attack)].get();
                }
            } else {
                //遠い時
                //タックルか追跡
                if(ran == 3){
                    m_activeAction = m_actionArray[int(ActState::Tackle)].get();
                } else {
                    m_activeAction = m_actionArray[int(ActState::Chase)].get();
                }
            }
        }
        m_activeAction->Start();
    };

    m_stateChangeFunc(1000.0f);
}

void Troll::Update() {
	ActArg arg;
	arg.charaCon = &m_CharaCon;
	arg.model = m_model;
	arg.player = stage->GetPlayer();
    arg.changeAct = m_stateChangeFunc;
    m_activeAction->Continue(arg);

    armCollision.Update();
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
