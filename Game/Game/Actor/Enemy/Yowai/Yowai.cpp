#include "stdafx.h"
#include "Yowai.h"

Yowai::Yowai( IStage * stage ) : Actor(10, stage){
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
		desc.walkMax = 100;

		desc.gravity = 900;
		desc.jumpPower = 500;

		desc.userIndex = enCollisionAttr_Enemy;
		desc.userPointer = this;

		m_chara.Init( desc );
	}

	//ステート
	{
		
	}
}

Yowai::~Yowai(){}
