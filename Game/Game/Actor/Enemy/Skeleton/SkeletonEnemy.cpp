#include "stdafx.h"
#include "SkeletonEnemy.h"
#include "Act/Attack.h"
#include "Act/Chase.h"
#include "Act/Idle.h"
using namespace SkeletonAct;

SkeletonEnemy::SkeletonEnemy( IStage * stage ) : Actor( 5, stage ){
	//キャラコン
	{
		CharaConDesc desc;

		desc.radius = 8;
		desc.height = 24;

		desc.position = CVector3( 0, 50, 0 );

		desc.walkAccel = 10;
		desc.walkAccelAir = 1;
		desc.walkMax = 100;

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
		m_model.Init( L"Assets/modelData/Skeleton.cmo", m_animClip, int( Anim::Num ) );
		m_model.SetPos( GetPos() );
	}

	//ステートの初期化
	{
		stateArray[int( Anim::Idle )].reset( new Idle() );
		stateArray[int( Anim::Chase )].reset( new Chase() );
		stateArray[int( Anim::Attack1 )].reset( new Attack(Anim::Attack1, Anim::Attack2 ) );
		stateArray[int( Anim::Attack2 )].reset( new Attack(Anim::Attack2, Anim::Attack1 ) );
		ChangeAct( Anim::Idle );
	}

	//剣の初期化
	{
		Bone* b = m_model.GetModel().GetSkeleton().GetBone( 4 );
		m_sword.Init( b, this, { 13,5,5 }, L"Assets/modelData/SkeSword.cmo" , false);
		m_sword.SetOffset( { 12, 0, 0 } );
		m_sword.SetCool( 1 );
	}

	m_hpBar.Init( L"Assets/sprite/HpOut.dds", L"Assets/sprite/HpIn.dds", 50, 2 );
}

SkeletonEnemy::~SkeletonEnemy(){}

void SkeletonEnemy::Update(){
	if( m_isDeath ){
		return;
	}

	//ステートのアップデート
	nowAct->Update(this);

	//位置をモデルに適用
	m_model.SetPos( GetPos() );

	//死亡
	if( m_nowHP == 0 ){
		m_model.SetActive( false );
		m_chara.SetActive( false );
		m_sword.SetActive( false );
		m_isDeath = true;
	}

	//各種アップデート
	m_hpBar.SetPercent( GetHPPer() );
	m_hpBar.SetPos( GetPos() + CVector3::Up() * 50 );
	Actor::Update();
	m_model.Update();
	m_sword.Update();
}

void SkeletonEnemy::ChangeAct( Anim state ){
	Act* a = stateArray[int( state )].get();
	if( a != nowAct ){
		nowAct = a;
		a->Start(this);
	}
}
