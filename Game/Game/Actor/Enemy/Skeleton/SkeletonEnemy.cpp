#include "stdafx.h"
#include "SkeletonEnemy.h"

SkeletonEnemy::SkeletonEnemy( IStage * stage ) : Actor( 5, stage ){
	//キャラコン
	{
		CharaConDesc desc;

		desc.radius = 8;
		desc.height = 24;

		desc.position = CVector3( 0, 50, 0 );

		desc.walkAccel = 10;
		desc.walkAccelAir = 1;
		desc.walkMax = 150;

		desc.gravity = 900;
		desc.jumpPower = 500;

		desc.userIndex = enCollisionAttr_Enemy;
		desc.userPointer = this;

		m_chara.Init( desc );
	}

	//アニメーションクリップとモデル
	{
		m_animClip [int( Anim::Idle )].Load( L"Assets/animData/Skeleton_Idle.tka", true );
		m_animClip [int( Anim::Walk )].Load( L"Assets/animData/Skeleton_Walk.tka", true );
		m_animClip [int( Anim::Attack1 )].Load( L"Assets/animData/Skeleton_Attack1.tka", false );
		m_animClip [int( Anim::Attack2 )].Load( L"Assets/animData/Skeleton_Attack2.tka", false );
		m_model.Init( L"Assets/modelData/Skeleton.cmo", m_animClip, int( Anim::Num ) );
		m_model.SetPos( GetPos() );
	}

}

SkeletonEnemy::~SkeletonEnemy(){}

void SkeletonEnemy::Update(){
	if( g_pad->IsTrigger( enButtonA ) ){
		m_model.Play( int( Anim::Walk ), 0.5f );
	}

	m_chara.Excecute();
	m_model.SetPos( GetPos() );

	Actor::Update();
	m_model.Update();
}
