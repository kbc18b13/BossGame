#include "stdafx.h"
#include "TrollHip.h"
#include "graphics/SkinModelRender.h"
#include "Actor/Player/Player.h"
#include "Scene/Stage1.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;

namespace EnemySpace{

TrollHip::TrollHip( TrollBodyCollision& col ) : bodyCol(col){}

void TrollHip::SubStart( Actor* t ){

	onJump = false;
	first = true;
	waitTime = 2.0f;
}

void TrollHip::Update( Actor* t ){
	CVector3 motion;
	float plength = 0;
	//�ŏ��̈�񂾂����s
	if( first ){
		//�W�����v�x�N�g���B�����ɂ��傤�ǃv���C���[��ɒ��n����悤�Ɉړ��x�N�g����������B
		const float jumpPower = 600;

		CVector3 motion = m_target->GetPos() - m_chara->GetPosition();
		plength = motion.Length();

		//�؋󎞊�
		float airTime = ( jumpPower / m_chara->GetGravity());

		motion /= airTime;

		motion.y += jumpPower;

		m_chara->SetVelocity( motion );

		first = false;
	}

	if( m_chara->GetVelocity().y < 0 ){
		bodyCol.StartAttack();
		m_model->Play( int( AnimState::Hip ), 0.2f );
	}

	m_model->SetPos( m_chara->Excecute( CVector3::Zero(), false ) );

	//�W�����v��ɒ��n������5�b�҂��Ď���
	if( !onJump ){
		if( !m_chara->OnGround() ){
			onJump = true;
		}
	} else if( m_chara->OnGround() ){
		waitTime -= GameTime::GetDeltaTime();
		if( waitTime <= 1.8f ){
			bodyCol.EndAttack();
		}
		if( waitTime <= 0 ){
			ActEnd( int( ActState::Wait ));
		}
	}
}

}