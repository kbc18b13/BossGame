#include "stdafx.h"
#include "Player.h"
#include "physics/CollisionAttr.h"
#include "graphics/RenderObjectManager.h"
#include "Act/Attack.h"
#include "Act/Idle.h"
#include "Act/Walk.h"
#include "Act/Guard.h"
#include "Act/Roll.h"

#include "Util/DisplayText.h"
#include "Scene/IStage.h"

using namespace PlayerAct;

Player::Player(IStage* stage) : Actor( 10 , stage){
	//アニメーションクリップ読み込み
	{
		m_animClip[int( Anim::Walk )].Load( L"Assets/animData/TestChara_Run.tka", true );
		m_animClip[int( Anim::Idle )].Load( L"Assets/animData/TestChara_Idle.tka", true );
		m_animClip[int( Anim::Slash1 )].Load( L"Assets/animData/TestChara_Slash.tka" );
		m_animClip[int( Anim::Slash2 )].Load( L"Assets/animData/TestChara_Slash2.tka" );
		m_animClip[int( Anim::Slash3 )].Load( L"Assets/animData/TestChara_Slash3.tka" );
		m_animClip[int( Anim::Slash4 )].Load( L"Assets/animData/TestChara_Slash4.tka" );
		m_animClip[int( Anim::Guard )].Load( L"Assets/animData/TestChara_Guard.tka" );
		m_animClip[int( Anim::Roll )].Load( L"Assets/animData/TestChara_Roll.tka" );
	}

	//cmoファイルの読み込み。
	m_model.Init( L"Assets/modelData/TestChara.cmo", m_animClip, int( Anim::Num ) );

	CharaConDesc desc;
	{
		desc.radius = 8;
		desc.height = 24;

		desc.position = CVector3( 0, 50, 0 );

		desc.walkAccel = 10;
		desc.walkAccelAir = 1;
		desc.walkMax = 150;

		desc.gravity = 900;
		desc.jumpPower = 500;

		desc.userIndex = enCollisionAttr_Player;
		desc.userPointer = this;
	}
	m_charaCon.Init( desc );//キャラコンの初期化

	//アクトステートの初期化
	{
		m_actArray[int( Anim::Slash4 )].reset( new PlayerAct::Attack( Anim::Slash4, Anim::SlashEnd ) );
		m_actArray[int( Anim::Slash3 )].reset( new PlayerAct::Attack( Anim::Slash3, Anim::Slash4 ) );
		m_actArray[int( Anim::Slash2 )].reset( new PlayerAct::Attack( Anim::Slash2, Anim::Slash3 ) );
		m_actArray[int( Anim::Slash1 )].reset( new PlayerAct::Attack( Anim::Slash1, Anim::Slash2 ) );
		m_actArray[int( Anim::Idle )].reset( new Idle() );
		m_actArray[int( Anim::Walk )].reset( new Walk() );
		m_actArray[int( Anim::Guard )].reset( new Guard() );
		m_actArray[int( Anim::Roll )].reset( new Roll() );

		ChangeActDefault();
	}

	//剣の初期化
	m_sword.Init( m_model.GetModel().GetSkeleton().GetBone( L"Hand_L" ), this ,
				  { 13,5,5 } , L"Assets/modelData/Sword.cmo" );
	m_sword.SetOffset( { 12, 0, 0 } );

	//盾の初期化
	m_shield.Init( m_model.GetModel().GetSkeleton().GetBone( L"Hand_R" ), this );

	//HPバーの初期化
	m_hpBar.Init( L"Assets/sprite/HpOut.dds", L"Assets/sprite/HpIn.dds", 1000, 25 );
	m_hpBar.SetPosCenterZero( CVector2( 625, 325 ) );
}


Player::~Player(){}

void Player::Update(){
	if( m_isDeath ){
		return;
	}

	//シャドウマップの移動
	{
		g_ROManager.GetShadowMap().UpdateLight( GetPos() + CVector3( 400, 400, 400 ), CVector3( -1, -1, -1 ) );
	}

	//敵のロックオン
	if( g_pad->IsTrigger( enButtonRB3 ) ){
		m_camera.TurnLockOn( m_stage );
	}

	//ステート
	m_nowAct->ChangeState( this );
	m_nowAct->Update( this );

	//モデル位置
	m_model.SetPos( m_charaCon.GetPosition() );

	//モデル回転
	if( m_camera.IsLockOn() ){
		rot = Util::LookRotXZ( m_camera.GetLockOnPos() - GetPos() );
	}
	m_model.SetRot( rot );

	//カメラの更新
	m_camera.Update( GetPos() + CVector3::Up() * 40);

	//HPバーの更新
	m_hpBar.SetPercent( Actor::GetHPPer() );

	//スタミナバーの更新
	m_stamina.Update();

	Actor::Update();
	m_model.Update();
	m_sword.Update();
	m_shield.Update();

	//死亡
	if( m_nowHP == 0 ){
		m_stage->EndStage();
		m_model.SetActive( false );
		m_charaCon.SetActive( false );
		m_sword.SetActive( false );
		m_shield.SetActive( false );
		m_isDeath = true;
		DisplayText::display( L"YOU DIED", CVector3( 0.7f, 0, 0 ) );
	}
}

bool Player::Damage( UINT damage, float coolTime, Actor* source ){
	if( m_nowAct == m_actArray[int( Anim::Guard )].get() ){
		CVector3 v( 0, 0, 1 );
		rot.Multiply( v );

		CVector3 toSource = source->GetPos() - GetPos();
		toSource.y = 0;
		toSource.Normalize();

		if( acosf( v.Dot( toSource ) ) < CMath::DegToRad( 30 ) ){
			damage = 0;
		}
	}
	return Actor::Damage( damage, coolTime, source );
}

void Player::ChangeActDefault(){
	if( g_pad->IsTrigger( enButtonB ) && ChangeAct( Anim::Roll ) ){
		return;
	}

	if( g_pad->IsPress( enButtonLB1 ) ){
		ChangeAct( Anim::Guard);
		return;
	}

	if( g_pad->IsTrigger( enButtonRB1 ) && ChangeAct( Anim::Slash1 ) ){
		return;
	}

	if( g_pad->GetLStickVec().LengthSq() > 0.01f ){
		ChangeAct( Anim::Walk);
		return;
	}

	ChangeAct( Anim::Idle);
}

bool Player::ChangeAct( Anim act ){
	Act* a = m_actArray[int( act )].get();
	//スタミナが足りない場合は変更せずfalseを返す。
	if( a->ConsumeStamina( m_stamina ) ){
		m_nowAct = a;
		m_nowAct->Start( this );
		return true;
	}
	return false;
}
