#include "stdafx.h"
#include "SlimeRollAttack.h"
#include "Actor/Actor.h"
#include "..\Slime.h"

namespace EnemySpace{

static float c_rollRadius = 60;

void SlimeRollAttack::Init( SkinModelRender * model, CharaConEx * chara, Actor * target ){
	EnemyAct::Init( model, chara, target );
	m_sound.Init( L"Assets/sound/rollAttack.wav" );
	m_rollShape.Create( 30, c_rollRadius*0.5f );
	m_rollColl.Create( m_rollShape );
	m_rollColl.SetMask( btCollisionObject::CF_NO_CONTACT_RESPONSE );
	m_rollColl.SetGroup(btCollisionObject::CollisionFlags::CF_Enemy);
	m_rollColl.SetUserPointer( chara->GetUserPointer() );
	m_rollColl.SetUserIndex(enCollisionAttr_Enemy);
}

void SlimeRollAttack::SubStart( Actor * a ){
	rolling = false;
	rollTimer = 3.0f;
	damageCool = 0;
	m_soundTimer = 0.0f;
	m_model->Play( int( Slime::Anim::RollAttack ), 0.3f );
}

void SlimeRollAttack::Update( Actor * a ){
	//��
	if( m_soundTimer <= 0.0f ){
		m_sound.Play( );
		m_soundTimer = 1.0f;
	}

	if( !rolling ){
		m_model->AddRot( CQuaternion::CreateRotDeg( CVector3::AxisY(), 360 * GameTime::GetDeltaTime() ) );
		m_soundTimer -= GameTime::GetDeltaTime()*2;
		//�ŏ��̃A�j���[�V�������~�܂������]���J�n����B
		if( !m_model->IsPlaying() ){
			rolling = true;
			g_physics.AddCollision( m_rollColl );
		}
		return;
	}

	if( rollTimer > 0 ){
		m_rollColl.SetPos( a->GetPos() + CVector3(0, 20 ,0) );

		CVector3 toP = m_target->GetPos() - a->GetPos();
		CVector3 toPNorm = toP;
		toPNorm.Normalize();

		//�v���C���[�Ƀ_���[�W
		damageCool -= GameTime::GetDeltaTime();

		if(damageCool <= 0 && toP.LengthSq() < pow2( c_rollRadius ) && toP.y < 10){
			m_target->Damage( 10, a );
			m_target->AddVelocity( toPNorm * 500 + CVector3::Up()*100);
			damageCool = 0.5f;
		}

		//�v���C���[��ǂ�
		m_chara->Excecute( toPNorm, 1.2f, 0.7f,false );

		//��]
		m_model->AddRot( CQuaternion::CreateRotDeg( CVector3::AxisY(), 1200 * GameTime::GetDeltaTime() ) );
		m_soundTimer -= GameTime::GetDeltaTime() * 3;

		//���Ԃ���������~�߂�B
		rollTimer -= GameTime::GetDeltaTime();

	} else{
		m_model->Play( int(Slime::Anim::RollEnd ), 0.1f);
		m_model->AddRot( CQuaternion::CreateRotDeg( CVector3::AxisY(), 360 * GameTime::GetDeltaTime() ) );
		m_soundTimer -= GameTime::GetDeltaTime()*2;
		//��]��̃A�j���[�V�������I�������I���B
		if( !m_model->IsPlaying() ){
			ActEnd( int( Slime::ActE::Idle ) );
		}
	}
}

void SlimeRollAttack::End( Actor * a ){
	g_physics.RemoveCollision( m_rollColl );
}

}