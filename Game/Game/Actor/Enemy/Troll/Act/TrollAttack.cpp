#include "stdafx.h"
#include "TrollAttack.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;

namespace EnemySpace{

TrollAttack::TrollAttack( ArmWeapon& arm ) : m_arm( arm ){}

void TrollAttack::Init( SkinModelRender * model, CharaConEx * chara, Actor * target ){
	EnemyAct::Init( model, chara, target );
	model->AddEventFunc( "Attack", [&](){
		m_arm.AttackStart();
	} );
}

void TrollAttack::SubStart( Actor* t ){
	m_isSecond = false;
	m_model->Play( int( AnimState::Attack ), 0.2f );
	m_arm.SetBone( m_model->GetModel().GetSkeleton().GetBone( L"Hand_L" ) );
}

void TrollAttack::Update( Actor* t ){
	CVector3 toP = m_target->GetPos() - m_chara->GetPosition();

	m_model->SetPos( m_chara->Excecute( CVector3::Zero(), false ) );

	//攻撃判定が開始するまではプレイヤーのほうを向く
	if( !m_arm.IsAttacking() && !m_isSecond){
		m_model->SetRot( Util::LookRotXZ( toP ) );
	}

	//アニメーション終了
	if( !m_model->IsPlaying() ){

		//近ければ2撃目
		if( !m_isSecond && toP.LengthSq() < pow2( 300 ) ){
			m_chara->SetVelocity( m_model->GetFront() * 500 + CVector3::Up() * 150 );
			m_arm.SetBone( m_model->GetModel().GetSkeleton().GetBone( L"Hand_R" ) );
			m_model->Play( int( AnimState::Attack2 ), 0.2f );
			m_isSecond = true;
			m_arm.AttackEnd();
		} else{
			ActEnd( int( ActState::Wait ) );
		}
	}
}

void TrollAttack::End( Actor * a ){
	m_arm.AttackEnd();
}

}