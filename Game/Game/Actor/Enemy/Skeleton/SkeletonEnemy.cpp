#include "stdafx.h"
#include "SkeletonEnemy.h"

#include "Scene/IStage.h"
#include "Actor/Player/Player.h"

#include "Act/SkeAttack.h"
#include "Act/SkeIdle.h"
#include "Act/SkeJumpAttack.h"
#include "Actor/Enemy/Act/Chase.h"
#include "Actor/Enemy/Act/SideWalk.h"
#include "Actor/Enemy/Act/Hit.h"

using namespace EnemySpace;

SkeletonEnemy::SkeletonEnemy( IStage * stage ) : Actor( 60, stage ){
	//音
	{
		m_se_swordSwing.Init( L"Assets/sound/sword_swing.wav" );
		m_se_swordSlash.Init( L"Assets/sound/sword_slash2.wav" );
	}

	//キャラコン
	{
		CharaConDesc desc;

		desc.radius = 8;
		desc.height = 24;

		desc.position = CVector3( 0, 50, 0 );

		desc.walkAccel = 10;
		desc.walkAccelAir = 1;
		desc.walkMax = 120;

		desc.gravity = 900;
		desc.jumpPower = 500;

		desc.userIndex = enCollisionAttr_Enemy;
		desc.userPointer = this;

		m_chara.Init( desc );
	}

	//アニメーションクリップとモデル
	{
		m_animClip[int( Anim::Idle )].Load( L"Assets/animData/Skeleton_Idle.tka", true );
		m_animClip[int( Anim::Chase )].Load( L"Assets/animData/Skeleton_Walk.tka", true );
		m_animClip[int( Anim::Attack1 )].Load( L"Assets/animData/Skeleton_Attack1.tka", false );
		m_animClip[int( Anim::Attack2 )].Load( L"Assets/animData/Skeleton_Attack2.tka", false );
		m_animClip[int( Anim::JumpAttack )].Load( L"Assets/animData/Skeleton_JumpAttack.tka", false );
		m_animClip[int( Anim::Hit )].Load( L"Assets/animData/Skeleton_Hit.tka", false );
		m_model.Init( L"Assets/modelData/Skeleton.cmo", m_animClip, int( Anim::Num ) );
		m_model.SetPos( GetPos() );
	}

	//ステートの初期化
	{
		m_stateArray[int( ActE::Idle )].reset( new SkeIdle() );
		m_stateArray[int( ActE::Chase )].reset( new Chase( int( Anim::Chase ), int( ActE::Idle ), 60.0f ));
		m_stateArray[int( ActE::Attack )].reset( new SkeAttack( m_sword, int( Anim::Attack1 ), 2 ) );
		m_stateArray[int( ActE::SideWalk )].reset( new SideWalk( int( Anim::Chase ), int( ActE::Idle ) ));
		m_stateArray[int( ActE::Hit )].reset( new Hit(int(Anim::Hit), int(ActE::Idle)));
		m_stateArray[int( ActE::JumpAttack )].reset( new SkeJumpAttack( m_sword ) );

		//必要なアニメーションイベント
		m_model.AddEventFunc( "Attack", [this](){
			if( NowActIs( int( ActE::Attack ) ) || NowActIs( int( ActE::JumpAttack ) ) ){
				m_sword.AttackStart();
				m_se_swordSwing.Play();
			}
		} );

		//初期化
		for( auto& a : m_stateArray ){
			a->Init( &m_model, &m_chara, m_stage->GetPlayer() );
		}

		m_nowAct = GetAct( int( Anim::Idle ) );
		m_nowAct->Start(this);
	}

	//剣の初期化
	{
		Bone* b = m_model.GetModel().GetSkeleton().GetBone( L"Hand_R" );
		m_sword.Init( b, this, { 13,5,5 }, L"Assets/modelData/SkeSword.cmo", false );
		m_sword.GetModel().LoadSpecularTex( L"Assets/modelData/SkeSwordSpec.dds" );
		m_sword.SetOffset( { -12, 0, 0 } );
		m_sword.SetKnockBack( CVector3( 0, 20, 50 ) );
		m_sword.SetDamage( 10 );
		m_sword.SetSound( &m_se_swordSlash );
	}

	m_hpBar.Init( L"Assets/sprite/HpOut.dds", L"Assets/sprite/HpIn.dds", 50, 2 );
}

SkeletonEnemy::~SkeletonEnemy(){}

void SkeletonEnemy::Update(){
	if( m_isDeath ){
		return;
	}

	//位置をモデルに適用
	m_model.SetPos( GetPos() );

	//各種アップデート
	ActStateUpdate();
	m_hpBar.SetPercent( GetHPPer() );
	m_hpBar.SetPos( GetPos() + CVector3::Up() * 50 );
	m_model.Update();
	m_sword.Update();
}

void SkeletonEnemy::OnDeath(){
	m_model.SetActive( false );
	m_chara.SetActive( false );
	m_sword.SetActive( false );
	m_hpBar.SetPercent( 0 );
}

Act * SkeletonEnemy::GetAct( int index ){
	return m_stateArray[index].get();
}
