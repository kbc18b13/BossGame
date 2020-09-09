#include "stdafx.h"
#include "Player.h"
#include "physics/CollisionAttr.h"
#include "graphics/RenderObjectManager.h"
#include "Act/Attack.h"
#include "Act/Walker.h"
#include "Act/Guard.h"
#include "Act/Roll.h"
#include "Act/Damage.h"
#include "Act/JumpAtk.h"
#include "Act/OnLadder.h"

#include "Util/DisplayText.h"
#include "Scene/IStage.h"

using namespace PlayerSpace;

Player::Player() : Actor( 150, nullptr ){
	dashButton.SetButton( enButtonB );
	//音声初期化
	{
		m_se_swordSwing.Init( L"Assets/sound/sword_swing.wav" );
		m_se_swordSlash.Init( L"Assets/sound/sword_slash.wav" );
		m_se_guard.Init( L"Assets/sound/guard.wav" );
	}

	//モデル読み込み
	{
		m_animClip[int( Anim::Walk )].Load( L"Assets/animData/Chara_Run.tka", true );
		m_animClip[int( Anim::Idle )].Load( L"Assets/animData/Chara_Idle.tka", true );
		m_animClip[int( Anim::Slash1 )].Load( L"Assets/animData/Chara_Slash.tka" );
		m_animClip[int( Anim::Slash2 )].Load( L"Assets/animData/Chara_Slash2.tka" );
		m_animClip[int( Anim::HeavySlash )].Load( L"Assets/animData/Chara_HeavySlash.tka" );
		m_animClip[int( Anim::Guard )].Load( L"Assets/animData/Chara_Guard.tka" );
		m_animClip[int( Anim::Roll )].Load( L"Assets/animData/Chara_Roll.tka" );
		m_animClip[int( Anim::Damage )].Load( L"Assets/animData/Chara_Damage.tka" );
		m_animClip[int( Anim::Jump )].Load( L"Assets/animData/Chara_Jump.tka" );
		m_animClip[int( Anim::JumpAtkL )].Load( L"Assets/animData/Chara_JumpAttackL.tka" );
		m_animClip[int( Anim::JumpAtkH )].Load( L"Assets/animData/Chara_JumpAttackH.tka" );
		m_animClip[int( Anim::OnLadder )].Load( L"Assets/animData/Chara_Ladder.tka" , true);


		//cmoファイルの読み込み。
		m_model.Init( { L"Assets/modelData/Chara.cmo", m_animClip, int( Anim::Num ) } );
		m_model.LoadSpecularTex( L"Assets/modelData/charaSpec.dds" );

		m_model.AddEventFunc( "Attack", [&](){
			if( NowActIs( int( Act::Slash ) ) || NowActIs( int( Act::JumpAtk ) ) ){
				m_se_swordSwing.Play();
				m_sword.AttackStart();
			}
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
		m_actArray[int( Act::Slash )].reset( new Attack( Anim::Slash1, 2, &m_model , &dashButton) );
		m_actArray[int( Act::JumpAtk )].reset( new JumpAtk() );
		m_actArray[int( Act::Walker )].reset( new Walker( &dashButton ) );
		m_actArray[int( Act::Guard )].reset( new Guard() );
		m_actArray[int( Act::Roll )].reset( new Roll() );
		m_actArray[int( Act::Damage )].reset( new PlayerSpace::Damage() );
		m_actArray[int( Act::OnLadder )].reset( new PlayerSpace::OnLadder() );

		//必要なものを注入
		for( auto& a : m_actArray ){
			a->Init( &m_model, &m_chara, &m_sword, &m_camera, &m_stamina );
		}

		m_nowAct = GetAct( int( Act::Walker ) );
	}
	//剣の初期化
	m_sword.Init( m_model.GetModel().GetSkeleton().GetBone( L"Hand_L" ), this,
				  { 5,5,13 }, L"Assets/modelData/SkeSword.cmo", true );
	m_sword.GetModel().LoadSpecularTex( L"Assets/modelData/SkeSwordSpec.dds" );
	m_sword.SetOffset( { 0, 2, 15 } );
	m_sword.SetModelOffset( { 0, 2, 0 } );
	m_sword.SetModelRot( CQuaternion::CreateRotDeg( CVector3::AxisY(), 45 ) );
	m_sword.SetKnockBack( CVector3( 0, 100, 100 ) );
	m_sword.SetSound( &m_se_swordSlash );

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
	dashButton.Update();
	//ステートのアップデート
	ActStateUpdate();

	//モデル位置
	m_model.SetPos( m_chara.GetPosition() );

	//ロックオン時の回転
	if( m_camera.IsLockOn() && m_nowAct != GetAct( int( Act::Roll ) ) ){
		m_model.SetRot( Util::LookRotXZ( m_camera.GetLockOnPos() - GetPos() ) );
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

	if( GetPos().y < -100 && !m_fallDeath ){
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
			if( m_stamina.Consume( damage ) ){
				damage = 0;
				m_se_guard.Play();
			}
		}
	}
	if( damage != 0 ){
		ChangeAct( int( Act::Damage ) );
	}
	return Actor::Damage( damage, source );
}

void Player::SetOnLadder( Ladder& ladder ){
	::Act* const a = GetAct( int( Act::OnLadder ) );
	OnLadder* const ladderAct = static_cast<OnLadder*>( a );
	ladderAct->SetLadder( ladder );
	ChangeAct( int( Act::OnLadder ) );
}

Act* Player::GetAct( int index ){
	return m_actArray[index].get();
}