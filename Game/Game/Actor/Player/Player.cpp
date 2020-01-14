#include "stdafx.h"
#include "Player.h"
#include "physics/CollisionAttr.h"
#include "graphics/RenderObjectManager.h"
#include "Act/Attack.h"
#include "Act/Idle.h"
#include "Act/Walk.h"
#include "Act/Guard.h"
#include "Act/Roll.h"

using namespace PlayerAct;

Player::Player(IStage* stage) : Actor( 10 , stage){
	//�A�j���[�V�����N���b�v�ǂݍ���
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

	//cmo�t�@�C���̓ǂݍ��݁B
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
	m_charaCon.Init( desc );//�L�����R���̏�����

	//�A�N�g�X�e�[�g�̏�����
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

	//�J�����̏�����
	m_camera.SetVec( { 0, 80, -80 } );

	//���̏�����
	m_sword.Init( m_model.GetModel().GetSkeleton().GetBone( L"Hand_L" ), this );
	m_sword.SetOffset( { 12, 0, 0 } );

	//���̏�����
	m_shield.Init( m_model.GetModel().GetSkeleton().GetBone( L"Hand_R" ), this );

	//HP�o�[�̏�����
	m_hpBar.Init( L"Assets/sprite/HpOut.dds", L"Assets/sprite/HpIn.dds", 1000, 25 );
	m_hpBar.SetPosCenterZero( CVector2( 625, 325 ) );
}


Player::~Player(){}

void Player::Update(){
	//�V���h�E�}�b�v�̈ړ�
	{
		g_ROManager.GetShadowMap().UpdateLight( GetPos() + CVector3( 400, 400, 400 ), CVector3( -1, -1, -1 ) );
	}

	if( g_pad->IsTrigger( enButtonRB3 ) ){
		m_camera.TurnLockOn( m_stage );
	}

	m_nowAct->ChangeState( this );
	m_nowAct->Update( this );

	CVector3 speed = m_charaCon.GetVelocity();
	//���f���ʒu
	m_model.SetPos( m_charaCon.GetPosition() );
	//���f����]

	if( m_camera.IsLockOn() ){
		rot = Util::LookRotXZ( m_camera.GetLockOnPos() - GetPos() );
	}/* else
		if( speed.x*speed.x + speed.z*speed.z > 1 ){
			float angle = atan2f( speed.x, speed.z );
			rot.SetRotation( CVector3::AxisY(), angle );
		}*/

	m_model.SetRot( rot );

	//�J�����̍X�V
	m_camera.Update( GetPos() + CVector3::Up() * 40 );

	//HP�o�[�̍X�V
	m_hpBar.SetPercent( Actor::GetHPPer() );

	//�X�^�~�i�o�[�̍X�V
	m_stamina.Update();

	Actor::Update();
	m_model.Update();
	m_sword.Update();
	m_shield.Update();
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
	//�X�^�~�i������Ȃ��ꍇ�͕ύX����false��Ԃ��B
	if( a->ConsumeStamina( m_stamina ) ){
		m_nowAct = a;
		m_nowAct->Start( this );
		return true;
	}
	return false;
}
