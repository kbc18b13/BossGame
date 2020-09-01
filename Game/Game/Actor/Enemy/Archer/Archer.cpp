#include "stdafx.h"
#include "Archer.h"
#include "Act/Idle.h"
#include "Act/Shot.h"
#include "Scene/IStage.h"
#include "Actor/Player/Player.h"

namespace EnemySpace{

Archer::Archer( IStage * stage ) : Actor(10 ,stage){
	//�L�����R��
	{
		CharaConDesc desc;

		desc.radius = 8;
		desc.height = 24;

		desc.position = CVector3( 0, 50, 0 );

		desc.walkAccel = 10;
		desc.walkAccelAir = 1;
		desc.walkMax = 120;

		desc.gravity = 900;
		desc.jumpPower = 500;

		desc.userIndex = enCollisionAttr_Enemy;
		desc.userPointer = this;

		m_chara.Init( desc );
	}

	//�A�j���[�V�����N���b�v�ƃ��f��
	{
		m_animClip[int( Anim::Idle )].Load( L"Assets/animData/Archer_Idle.tka", true );
		m_animClip[int( Anim::Shot )].Load( L"Assets/animData/Archer_Shot.tka", false );
		m_model.Init( { L"Assets/modelData/Archer.cmo", m_animClip, int( Anim::Num ) } );
		m_model.SetPos( GetPos() );
	}

	//�X�e�[�g�̏�����
	{
		m_stateArray[int( ActE::Idle )].reset( new Idle() );
		m_stateArray[int( ActE::Shot )].reset( new Shot() );

		//�K�v�ȃA�j���[�V�����C�x���g


		//������
		for( auto& a : m_stateArray ){
			a->Init( &m_model, &m_chara, m_stage->GetPlayer() );
		}

		m_nowAct = GetAct( int( Anim::Idle ) );
		m_nowAct->Start( this );
	}

	m_hpBar.Init( L"Assets/sprite/HpOut.dds", L"Assets/sprite/HpIn.dds", 50, 2 );
}

Archer::~Archer(){}

void Archer::Update(){
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
}

void Archer::OnDeath(){
	m_model.SetActive( false );
	m_chara.SetActive( false );
	m_hpBar.SetPercent( 0 );
}

Act* Archer::GetAct( int index ){
	return m_stateArray[index].get();
}

}