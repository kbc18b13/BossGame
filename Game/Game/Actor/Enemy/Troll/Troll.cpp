#include "stdafx.h"
#include "Troll.h"
#include "physics/CollisionAttr.h"
#include "Scene/Stage1.h"
#include "Actor/Player/Player.h"

#include "Act/ActAttack.h"
#include "Act/ActIdle.h"
#include "Act/ActStep.h"
#include "Act/ActChase.h"
#include "Act/ActTackle.h"
#include "Act/ActHip.h"

#include "graphics/RenderObjectManager.h"

using namespace TrollAct;

Troll::Troll(IStage* stage) : Actor(10, stage ){
    //モデル
	{
		m_animClip[int(AnimState::Walk)].Load(L"Assets/animData/Troll_Walk.tka", true);
		m_animClip[int(AnimState::Attack)].Load(L"Assets/animData/Troll_Attack.tka", false);
		m_animClip[int(AnimState::JumpUp)].Load(L"Assets/animData/Troll_Jump.tka", false);
		m_animClip[int(AnimState::JumpDown)].Load(L"Assets/animData/Troll_Fall.tka", false);
		m_animClip[int(AnimState::Idle)].Load(L"Assets/animData/Troll_Idle.tka", true);
        m_animClip[int(AnimState::Tackle)].Load(L"Assets/animData/Troll_Tackle.tka", true);
        m_animClip[int(AnimState::Hip)].Load(L"Assets/animData/Troll_Hip.tka", false);
		m_model.Init(L"Assets/modelData/Troll.cmo", m_animClip, int(AnimState::Num));
	}

    //キャラコン
	CharaConDesc desc;
	{
		desc.radius = 25;
		desc.height = 40;

		desc.position = CVector3(0, 0, 0);

		desc.walkAccel = 10;
		desc.walkAccelAir = 1;
		desc.walkMax = 100;

		desc.gravity = 900;
		desc.jumpPower = 500;

		desc.userIndex = enCollisionAttr_Enemy;
		desc.userPointer = this;
	}
	m_CharaCon.Init(desc); 

    //腕コリジョン
    Bone* arm = m_model.GetModel().GetSkeleton().GetBone(20);
    armCollision.Init(this, arm);

	m_hpBar.Init( L"Assets/sprite/HpOut.dds", L"Assets/sprite/HpIn.dds", 1000, 25);
	m_hpBar.SetPosLikeTex( CVector2( 1144, 563 ) );
}

Troll::~Troll() {
}

void Troll::Start() {
	m_actionArray[int(ActState::Attack)].reset(new ActAttack(armCollision));
	m_actionArray[int(ActState::Chase)].reset(new ActChase());
	m_actionArray[int(ActState::Wait)].reset(new ActIdle());
	m_actionArray[int(ActState::Step)].reset(new ActStep());
    m_actionArray[int(ActState::Tackle)].reset(new ActTackle());
    m_actionArray[int(ActState::Hip)].reset(new ActHip());

	ChangeAct( ActState::Wait );
}

void Troll::Update() {
    m_activeAction->Continue(this);

	//HPバー更新
	m_hpBar.SetPercent( Actor::GetHPPer() );

	//死亡
	if( m_nowHP == 0 ){
		m_stage->EndStage();
		DeleteGO( this );
	}

    m_model.Update();
    armCollision.Update();
    Actor::Update();
}

void Troll::SetPos(const CVector3 & pos) {
	m_CharaCon.SetPosition(pos);
	m_model.SetPos(pos);
}

void Troll::ChangeActDefault(){
	CVector3 toP = m_stage->GetPlayer()->GetPos() - m_CharaCon.GetPosition();

	//近い
	if( toP.LengthSq() < 100 * 100 ){
		if( Util::RandomInt( 0, 3 ) == 0 ){
			ChangeAct( ActState::Hip );
		} else{
			ChangeAct( ActState::Attack );
		}

		//遠い
	} else{
		if( Util::RandomInt( 0, 3 ) == 0 ){
			ChangeAct( ActState::Tackle );
		} else{
			ChangeAct( ActState::Chase );
		}
	}
}

void Troll::ChangeAct( ActState act ){
	TrollAct::Act* a = m_actionArray[int( act )].get();
	if( a != m_activeAction ){
		a->Start( this );
		m_activeAction = a;
	}
}
