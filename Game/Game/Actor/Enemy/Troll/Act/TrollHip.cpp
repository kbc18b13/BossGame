#include "stdafx.h"
#include "TrollHip.h"
#include "graphics/SkinModelRender.h"
#include "Actor/Player/Player.h"
#include "Scene/Stage1.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;

namespace EnemySpace{

TrollHip::TrollHip( TrollBodyCollision& col ) : bodyCol( col ){}

void TrollHip::SubStart( Actor* t ){
	isLanded = false;
	isAttacked = false;
	waitTime = 2.0f;

	//�W�����v�x�N�g���B�����ɂ��傤�ǃv���C���[��ɒ��n����悤�Ɉړ��x�N�g����������B
	const float jumpPower = 600;
	//�؋󎞊�
	float airTime = ( jumpPower / m_chara->GetGravity() );
	//�ǉ����鑬�x���v�Z
	CVector3 motion = m_target->GetPos() - m_chara->GetPosition();
	motion /= airTime;
	motion.y += jumpPower;
	m_chara->SetVelocity( motion );
}

void TrollHip::Update( Actor* t ){

	if( m_chara->GetVelocity().y < 0 && !isAttacked){
		bodyCol.StartAttack();
		m_model->Play( int( AnimState::Hip ), 0.2f );
		isAttacked = true;
	}

	m_model->SetPos( m_chara->Excecute( CVector3::Zero(), false ) );

	//�W�����v��ɒ��n��������b�҂��Ď��ցB
	if( m_chara->OnGround() && isAttacked ){
		isLanded = true;
		bodyCol.EndAttack();
	}
	if( isLanded ){
		waitTime -= GameTime::GetDeltaTime();
	}
	if( waitTime <= 0 ){
		ActEnd( int( ActState::Wait ) );
	}
}

}