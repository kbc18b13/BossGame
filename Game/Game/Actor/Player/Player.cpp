#include "stdafx.h"
#include "Player.h"
#include "physics/CollisionAttr.h"
#include "graphics/RenderObjectManager.h"
#include "Act/Attack.h"
#include "Act/Idle.h"
#include "Act/Walk.h"

using namespace PlayerAct;

Player::Player() : Actor( 10 ){
	//�A�j���[�V�����N���b�v�ǂݍ���
	{
		m_animClip[int( Anim::Walk )].Load( L"Assets/animData/TestChara_Run.tka", true );
		m_animClip[int( Anim::Idle )].Load( L"Assets/animData/TestChara_Idle.tka", true );
		m_animClip[int( Anim::Slash )].Load( L"Assets/animData/TestChara_Slash.tka" );
		m_animClip[int( Anim::Slash2 )].Load( L"Assets/animData/TestChara_Slash2.tka" );
		m_animClip[int( Anim::Slash3 )].Load( L"Assets/animData/TestChara_Slash3.tka" );
		m_animClip[int( Anim::Slash4 )].Load( L"Assets/animData/TestChara_Slash4.tka" );
		m_animClip[int( Anim::Guard )].Load( L"Assets/animData/TestChara_Guard.tka" );
	}

	//cmo�t�@�C���̓ǂݍ��݁B
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
	m_charaCon.Init( desc );//�L�����R���̏�����

	//�A�N�g�X�e�[�g�̏�����
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

	m_nowAct->ChangeState(m_actArg);
	m_nowAct->Update(m_actArg);

	CVector3 speed = m_charaCon.GetVelocity();
	//���f���ʒu
	m_model.SetPos( m_charaCon.GetPosition() );
	//���f����]

	if( m_camera.IsLockOn() ){
		rot = Util::LookRotXZ( m_camera.GetLockOnPos() - GetPos() );
	} else
		if( speed.x*speed.x + speed.z*speed.z > 1 ){
			float angle = atan2f( speed.x, speed.z );
			rot.SetRotation( CVector3::AxisY(), angle );
		}

	m_model.SetRot( rot );

	//�J�����̍X�V
	m_camera.Update( GetPos() + CVector3::Up() * 40 );

	//HP�o�[�̍X�V
	m_hpBar.SetPercent( Actor::GetHPPer() );

	Actor::Update();
	m_model.Update();
	m_sword.Update();
	m_shield.Update();
}

void Player::ChangeActDefault(){}

void Player::ChangeAct( PlayerAct::Act * anim ){}
