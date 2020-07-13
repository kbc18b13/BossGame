#include "stdafx.h"
#include "Slime.h"
#include "Act/SlimeIdle.h"
#include "Act/SlimeStrike.h"
#include "Act//SlimeAvoid.h"
#include "Act/SlimeRollAttack.h"
#include "..\Act\Chase.h"
#include "..\Act\Hit.h"
#include "Scene/IStage.h"
#include "Actor/Player/Player.h"

using namespace EnemySpace;

Slime::Slime( IStage * stage ) : Actor(50 ,stage){
	//��
	m_se_strike.Init( L"Assets/sound/strike.wav" );

	//�L�����R��
	{
		CharaConDesc desc;

		desc.radius = 14;
		desc.height = 20;

		desc.position = CVector3( 0, 50, 0 );

		desc.walkAccel = 3;
		desc.walkAccelAir = 1;
		desc.walkMax = 110;

		desc.gravity = 900;
		desc.jumpPower = 500;

		desc.userIndex = enCollisionAttr_Enemy;
		desc.userPointer = this;

		m_chara.Init( desc );
	}

	//�A�j���[�V�����N���b�v�ƃ��f��
	{
		m_animClip[int( Anim::Idle )].Load( L"Assets/animData/Slime_Idle.tka", true );
		m_animClip[int( Anim::Walk )].Load( L"Assets/animData/Slime_Walk.tka", true );
		m_animClip[int( Anim::Strike )].Load( L"Assets/animData/Slime_Strike.tka", false );
		m_animClip[int( Anim::HeavyStrike )].Load( L"Assets/animData/Slime_HeavyStrike.tka", false );
		m_animClip[int( Anim::RollAttack )].Load( L"Assets/animData/Slime_RollAttack.tka", false );
		m_animClip[int( Anim::RollEnd )].Load( L"Assets/animData/Slime_RollEnd.tka", false );
		m_animClip[int( Anim::Avoid )].Load( L"Assets/animData/Slime_Avoid.tka", false );
		m_animClip[int( Anim::Hit )].Load( L"Assets/animData/Slime_Hit.tka", false );
		m_model.Init( { L"Assets/modelData/Slime.cmo", m_animClip, int( Anim::Num ) } );
		m_model.LoadSpecularTex( L"Assets/modelData/SlimeSpec.dds" );
		m_model.SetPos( GetPos() );
	}

	//�X�e�[�g�̏�����
	{
		m_stateArray[int( ActE::Idle )].reset( new SlimeIdle() );
		m_stateArray[int( ActE::Chase )].reset( new Chase(int(Anim::Walk), int(ActE::Strike), 40) );
		m_stateArray[int( ActE::Strike )].reset( new SlimeStrike(m_weapon) );
		m_stateArray[int( ActE::Hit )].reset( new Hit(int(Anim::Hit), int(ActE::Idle)) );
		m_stateArray[int( ActE::Avoid )].reset( new SlimeAvoid() );
		m_stateArray[int( ActE::RollAttack )].reset( new SlimeRollAttack() );

		//�K�v�ȃA�j���[�V�����C�x���g
		m_model.AddEventFunc( "Attack", [this](){
			m_weapon.AttackStart();
			m_se_strike.Play();
		} );

		//������
		for( auto& a : m_stateArray ){
			a->Init( &m_model, &m_chara, m_stage->GetPlayer() );
		}

		m_nowAct = GetAct( int( ActE::Idle ) );
		m_nowAct->Start( this );
	}

	//�U������̏�����
	{
		Bone* b = m_model.GetModel().GetSkeleton().GetBone( L"Head" );
		m_weapon.Init( b, this, { 13,13,13 }, false);
		m_weapon.SetOffset( { 0, 0, 0 } );
		m_weapon.SetKnockBack( CVector3( 0, 20, 50 ) );
	}

	m_hpBar.Init( L"Assets/sprite/HpOut.dds", L"Assets/sprite/HpIn.dds", 50, 2 );
}

Slime::~Slime(){}

void Slime::Update(){
	if( m_isDeath ){
		return;
	}

	//�ʒu�����f���ɓK�p
	m_model.SetPos( GetPos() );

	//�e��A�b�v�f�[�g
	ActStateUpdate();
	m_hpBar.SetPercent( GetHPPer() );
	m_hpBar.SetPos( GetPos() + CVector3::Up() * 50 );
	m_model.Update();
	m_weapon.Update();
}

void Slime::OnDeath(){
	m_model.SetActive( false );
	m_chara.SetActive( false );
	m_weapon.SetActive( false );
	m_hpBar.SetPercent( 0 );
}

Act * Slime::GetAct( int index ){
	return m_stateArray[index].get();
}