#include "stdafx.h"
#include "Player.h"
#include "physics/CollisionAttr.h"
#include "graphics/RenderObjectManager.h"
#include "Act/Attack.h"
#include "Act/Idle.h"
#include "Act/Walk.h"

using namespace PlayerAct;

Player::Player() : Actor( 10 ){
	//アニメーションクリップ読み込み
	{
		m_animClip[int( Anim::Walk )].Load( L"Assets/animData/TestChara_Run.tka", true );
		m_animClip[int( Anim::Idle )].Load( L"Assets/animData/TestChara_Idle.tka", true );
		m_animClip[int( Anim::Slash )].Load( L"Assets/animData/TestChara_Slash.tka" );
		m_animClip[int( Anim::Slash2 )].Load( L"Assets/animData/TestChara_Slash2.tka" );
		m_animClip[int( Anim::Slash3 )].Load( L"Assets/animData/TestChara_Slash3.tka" );
		m_animClip[int( Anim::Slash4 )].Load( L"Assets/animData/TestChara_Slash4.tka" );
		m_animClip[int( Anim::Guard )].Load( L"Assets/animData/TestChara_Guard.tka" );
	}

	//cmoファイルの読み込み。
	m_model.Init( L"Assets/modelData/TestChara.cmo", m_animClip, int( Anim::Num ) );

	CharaConDesc desc;
	{
		desc.radius = 8;
		desc.height = 24;

		desc.position = CVector3( 0, 50, 0 );

		desc.walkAccel = 100;
		desc.walkAccelAir = 10;
		desc.walkBrake = 10;
		desc.walkMax = 150;

		desc.gravity = 900;
		desc.jumpPower = 500;

		desc.userIndex = enCollisionAttr_Player;
		desc.userPointer = this;
	}
	m_charaCon.Init( desc );//キャラコンの初期化

	//アクトステートの初期化
	{
		m_actArray[0].reset( new PlayerAct::Attack() );
		m_actArray[1].reset( new Idle() );
		m_actArray[2].reset( new Walk() );
		
		m_actArg.camera = &m_camera;
		m_actArg.chara = &m_charaCon;
		m_actArg.model = &m_model;
		m_actArg.changeAct = std::bind( &Player::ChangeAct, this, std::placeholders::_1 );
		m_actArg.changeActDefault = std::bind( &Player::ChangeActDefault, this );
	}

	//カメラの初期化
	m_camera.SetVec( { 0, 80, -80 } );

	//剣の初期化
	m_sword.Init( m_model.GetModel().GetSkeleton().GetBone( L"Hand_L" ), this );
	m_sword.SetOffset( { 12, 0, 0 } );

	//盾の初期化
	m_shield.Init( m_model.GetModel().GetSkeleton().GetBone( L"Hand_R" ), this );

	//HPバーの初期化
	m_hpBar.Init( L"Assets/sprite/HpOut.dds", L"Assets/sprite/HpIn.dds", 1000, 25 );
	m_hpBar.SetPosCenterZero( CVector2( 625, 325 ) );
}


Player::~Player(){}

void Player::Update(){
	//シャドウマップの移動
	{
		g_ROManager.GetShadowMap().UpdateLight( GetPos() + CVector3( 400, 400, 400 ), CVector3( -1, -1, -1 ) );
	}

	if( g_pad->IsTrigger( enButtonRB3 ) ){
		m_camera.TurnLockOn( m_stage );
	}

	m_nowAct->ChangeState(m_actArg);
	m_nowAct->Update(m_actArg);

	CVector3 speed = m_charaCon.GetVelocity();
	//モデル位置
	m_model.SetPos( m_charaCon.GetPosition() );
	//モデル回転

	if( m_camera.IsLockOn() ){
		rot = Util::LookRotXZ( m_camera.GetLockOnPos() - GetPos() );
	} else
		if( speed.x*speed.x + speed.z*speed.z > 1 ){
			float angle = atan2f( speed.x, speed.z );
			rot.SetRotation( CVector3::AxisY(), angle );
		}

	m_model.SetRot( rot );

	//カメラの更新
	m_camera.Update( GetPos() + CVector3::Up() * 40 );

	//HPバーの更新
	m_hpBar.SetPercent( Actor::GetHPPer() );

	Actor::Update();
	m_model.Update();
	m_sword.Update();
	m_shield.Update();
}

void Player::ChangeActDefault(){}

void Player::ChangeAct( PlayerAct::Act * anim ){}
