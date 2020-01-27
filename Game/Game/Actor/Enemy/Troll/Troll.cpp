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

#include "Util/DisplayText.h"
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
	m_armCollision.Init( arm, this, CVector3( 10.0f, 20.0f, 10.0f ), false );

	//体コリジョン
	m_bodyCollision.Init( this );

	m_hpBar.Init( L"Assets/sprite/HpOut.dds", L"Assets/sprite/HpIn.dds", 1000, 25);
	m_hpBar.SetPosLikeTex( CVector2( 1144, 563 ) );
	m_hpBar.SetColor( CVector4( 1, 0, 0, 1 ) );

	m_nameFont.SetText( L"BOSSEnemy" );
	m_nameFont.SetPos( CVector2( 150, 500 ) );
}

Troll::~Troll() {
}

void Troll::Start() {
	m_actionArray[int(ActState::Attack)].reset(new ActAttack(m_armCollision));
	m_actionArray[int(ActState::Chase)].reset(new ActChase());
	m_actionArray[int(ActState::Wait)].reset(new ActIdle());
	m_actionArray[int(ActState::Step)].reset(new ActStep());
    m_actionArray[int(ActState::Tackle)].reset(new ActTackle(m_bodyCollision));
    m_actionArray[int(ActState::Hip)].reset(new ActHip(m_bodyCollision));

	ChangeAct( ActState::Wait );
}

void Troll::Update() {
	//死亡時、アップデートはしない。
	if( m_isDeath ){
		return;
	}

	//現在のステートのアクションを実行
    m_activeAction->Continue(this);

	//HPバー更新
	m_hpBar.SetPercent( Actor::GetHPPer() );

	//死亡
	if( m_nowHP == 0 ){
		m_stage->EndStage();
		m_model.SetActive( false );
		m_armCollision.SetActive( false );
		m_bodyCollision.SetActive( false );
		m_CharaCon.SetActive( false );
		m_hpBar.SetActive( false );
		m_nameFont.SetActive( false );
		m_isDeath = true;
		DisplayText::display( L"VICTORY ARCHIVED" , CVector3(0.5f, 0.5f, 1.0f));
	}

	//各種アップデート
    m_model.Update();
    m_armCollision.Update();
	m_bodyCollision.Update();
    Actor::Update();
}

void Troll::SetPos(const CVector3 & pos) {
	m_CharaCon.SetPosition(pos);
	m_model.SetPos(pos);
}

void Troll::ChangeActDefault(){
	if( Util::RandomInt( 0, 4 ) == 0 ){
		ChangeAct( ActState::Step );
		return;
	}

	CVector3 toP = m_stage->GetPlayer()->GetPos() - m_CharaCon.GetPosition();

	//近い
	if( toP.LengthSq() < 100 * 100 ){
		if( Util::RandomInt( 0, 0 ) == 0 ){
			ChangeAct( ActState::Hip );
		} else{
			ChangeAct( ActState::Attack );
		}

		//遠い
	} else{
		if( Util::RandomInt( 0, 2 ) == 0 ){
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
