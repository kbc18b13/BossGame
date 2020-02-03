#include "stdafx.h"
#include "Yowai.h"

#include "Scene/IStage.h"
#include "Actor/Player/Player.h"

#include "Act/YowaAttack.h"
#include "Act/YowaIdle.h"
#include "Actor/Enemy/Act/Hit.h"
#include "Actor/Enemy/Act/Chase.h"

using namespace EnemySpace;

Yowai::Yowai( IStage * stage ) : Actor(3, stage){
	//モデル初期化
	{
		m_animClips[int( Anim::Idle )].Load( L"Assets/animData/Yowai_Idle.tka", true);
		m_animClips[int( Anim::Hit )].Load( L"Assets/animData/Yowai_Hit.tka", false );
		m_animClips[int( Anim::Attack )].Load( L"Assets/animData/Yowai_Attack.tka", false );
		m_animClips[int( Anim::Walk )].Load( L"Assets/animData/Yowai_Walk.tka", true );

		m_model.Init( L"Assets/modelData/Yowai.cmo", m_animClips, int( Anim::Num ) );
	}

	//キャラコン初期化
	{
		CharaConDesc desc;

		desc.radius = 8;
		desc.height = 24;

		desc.position = CVector3( 0, 50, 0 );

		desc.walkAccel = 10;
		desc.walkAccelAir = 1;
		desc.walkMax = 50;

		desc.gravity = 900;
		desc.jumpPower = 500;

		desc.userIndex = enCollisionAttr_Enemy;
		desc.userPointer = this;

		m_chara.Init( desc );
	}

	//ステート
	{
		m_stateArray[int( Anim::Idle )].reset( new YowaIdle() );
		m_stateArray[int( Anim::Walk )].reset( new Chase( int( Anim::Walk ), int( Anim::Attack ) ) );
		m_stateArray[int( Anim::Hit )].reset( new Hit( int( Anim::Hit ), int( Anim::Idle ) ) );
		m_stateArray[int( Anim::Attack )].reset( new YowaAttack( m_weapon));

		//初期化
		for( auto& a : m_stateArray ){
			a->Init( &m_model, &m_chara, m_stage->GetPlayer() );
		}

		m_nowAct = GetAct( int( Anim::Idle ) );
		m_nowAct->Start(this);
	}

	Bone* b = m_model.GetModel().GetSkeleton().GetBone( 2 );
	m_weapon.Init( b, this, { 5,5,5 }, false );
	m_weapon.SetOffset( CVector3( 0, 7, 0 ) );

	m_hpBar.Init( L"Assets/sprite/HpOut.dds", L"Assets/sprite/HpIn.dds", 50, 2 );
	m_hpBar.SetColor( CVector4( 1, 0, 0, 1 ) );
}

Yowai::~Yowai(){}

void Yowai::Update(){
	//死亡時、アップデートはしない。
	if( m_isDeath ){
		return;
	}

	//ステートのアップデート
	ActStateUpdate();

	m_model.SetPos( GetPos() );

	m_hpBar.SetPercent( GetHPPer() );
	m_hpBar.SetPos( GetPos() + CVector3::Up() * 50 );

	if( m_nowHP == 0 ){
		m_model.SetActive( false );
		m_chara.SetActive( false );
		m_weapon.SetActive( false );
		m_isDeath = true;
	}

	m_model.Update();
	m_weapon.Update();
}

Act * Yowai::GetAct( int index ){
	return m_stateArray[index].get();
}
