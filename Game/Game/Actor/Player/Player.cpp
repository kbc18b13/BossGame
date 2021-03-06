#include "stdafx.h"
#include "Player.h"
#include "physics/CollisionAttr.h"
#include "graphics/RenderObjectManager.h"
#include "Act/Attack.h"
#include "Act/Walker.h"
#include "Act/Guard.h"
#include "Act/Roll.h"
#include "Act/Damage.h"

#include "Util/DisplayText.h"
#include "Scene/IStage.h"

using namespace PlayerSpace;

Player::Player(IStage* stage) : Actor( 10 , stage){
	//モデル読み込み
	{
		m_animClip[int( Anim::Walk )].Load( L"Assets/animData/TestChara_Run.tka", true );
		m_animClip[int( Anim::Idle )].Load( L"Assets/animData/TestChara_Idle.tka", true );
		m_animClip[int( Anim::Slash1 )].Load( L"Assets/animData/TestChara_Slash.tka" );
		m_animClip[int( Anim::Slash2 )].Load( L"Assets/animData/TestChara_Slash2.tka" );
		m_animClip[int( Anim::Slash3 )].Load( L"Assets/animData/TestChara_Slash3.tka" );
		m_animClip[int( Anim::Slash4 )].Load( L"Assets/animData/TestChara_Slash4.tka" );
		m_animClip[int( Anim::HeavySlash )].Load( L"Assets/animData/TestChara_HeavySlash.tka" );
		m_animClip[int( Anim::Guard )].Load( L"Assets/animData/TestChara_Guard.tka" );
		m_animClip[int( Anim::Roll )].Load( L"Assets/animData/TestChara_Roll.tka" );
		m_animClip[int( Anim::Damage )].Load( L"Assets/animData/TestChara_Damage.tka" );

		//cmoファイルの読み込み。
		m_model.Init( L"Assets/modelData/TestChara.cmo", m_animClip, int( Anim::Num ) );

		m_model.AddEventFunc( "Attack", [&](){
			m_sword.AttackStart();
		} );
	}

	CharaConDesc desc;
	{
		desc.radius = 8;
		desc.height = 24;

		desc.position = CVector3( 0, 50, 0 );

		desc.walkAccel = 10;
		desc.walkAccelAir = 1;
		desc.walkMax = 120;

		desc.gravity = 900;
		desc.jumpPower = 400;

		desc.userIndex = enCollisionAttr_Player;
		desc.userPointer = this;
		desc.collisionFlag = btCollisionObject::CollisionFlags::CF_Player;
	}
	m_chara.Init( desc );//キャラコンの初期化

	//アクトステートの初期化
	{
		m_actArray[int( Act::Slash )].reset( new Attack( Anim::Slash1, 4 ) );
		m_actArray[int( Act::Walker )].reset( new Walker() );
		m_actArray[int( Act::Guard )].reset( new Guard() );
		m_actArray[int( Act::Roll )].reset( new Roll() );
		m_actArray[int( Act::Damage )].reset( new PlayerSpace::Damage() );

		//必要なものを注入
		for( auto& a : m_actArray ){
			a->Init( &m_model, &m_chara, &m_sword, &m_camera, &m_stamina );
		}

		m_nowAct = GetAct( int(Act::Walker ));
	}
	//剣の初期化
	m_sword.Init( m_model.GetModel().GetSkeleton().GetBone( L"Hand_L" ), this ,
				  { 13,5,5 } , L"Assets/modelData/Sword.cmo" , true);
	m_sword.SetOffset( { 12, 0, 0 } );
	m_sword.SetKnockBack( CVector3( 0, 100, 100 ) );

	//盾の初期化
	m_shield.Init( m_model.GetModel().GetSkeleton().GetBone( L"Hand_R" ), this );

	//HPバーの初期化
	m_hpBar.Init( L"Assets/sprite/HpOut.dds", L"Assets/sprite/HpIn.dds", 1000, 25 );
	m_hpBar.SetPosCenterZero( CVector2( 625, 325 ) );
	m_hpBar.SetColor( CVector4( 1, 0, 0, 1 ) );
}

Player::~Player(){}

void Player::Start(){
	//カメラ
	m_camera.Init( this );
}

void Player::Update(){
	if( m_isDeath ){
		return;
	}

	//シャドウマップの移動
	{
		g_ROManager.GetShadowMap().UpdateLight( GetPos() + CVector3( 400, 400, 400 ), CVector3( -1, -1, -1 ) );
	}

	//ステートのアップデート
	ActStateUpdate();

	//モデル位置
	m_model.SetPos( m_chara.GetPosition() );

	//ロックオン時の回転
	if( m_camera.IsLockOn() && m_nowAct != GetAct(int(Act::Roll))){
		m_model.SetRot(Util::LookRotXZ( m_camera.GetLockOnPos() - GetPos() ));
	}

	//カメラの更新
	m_camera.Update();

	//HPバーの更新
	m_hpBar.SetPercent( Actor::GetHPPer() );

	//スタミナバーの更新
	m_stamina.Update();

	//モデルなど
	m_model.Update();
	m_sword.Update();
	m_shield.Update();

	if( GetPos().y < -100 && !m_fallDeath){
		m_stage->EndStage();
		DisplayText::display( L"YOU DIED", CVector3( 0.7f, 0, 0 ) );
		m_fallDeath = true;
	}
}

void Player::OnDeath(){
	m_stage->EndStage();
	m_model.SetActive( false );
	m_chara.SetActive( false );
	m_sword.SetActive( false );
	m_shield.SetActive( false );
	m_hpBar.SetPercent( 0 );
	DisplayText::display( L"YOU DIED", CVector3( 0.7f, 0, 0 ) );
}

bool Player::Damage( UINT damage, Actor* source ){
	if( m_nowAct == m_actArray[int( Act::Guard )].get() ){
		CVector3 v( 0, 0, 1 );
		m_model.GetRot().Multiply( v );

		CVector3 toSource = source->GetPos() - GetPos();
		toSource.y = 0;
		toSource.Normalize();

		if( acosf( v.Dot( toSource ) ) < CMath::DegToRad( 80 ) ){
			if( m_stamina.Consume( damage * 10 ) ){
				damage = 0;
			}
		}
	}
	if( damage != 0 ){
		ChangeAct( int(Act::Damage) );
	}
	return Actor::Damage( damage, source);
}

Act* Player::GetAct( int index ){
	return m_actArray[index].get();
}