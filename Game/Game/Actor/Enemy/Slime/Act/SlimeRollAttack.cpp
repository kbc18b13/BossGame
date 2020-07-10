#include "stdafx.h"
#include "SlimeRollAttack.h"
#include "Actor/Actor.h"
#include "..\Slime.h"

namespace EnemySpace{

SlimeRollAttack::SlimeRollAttack(){
	m_sound.Init( L"Assets/sound/rollAttack.wav" );
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
		}
		return;
	}

	if( rollTimer > 0 ){
		CVector3 toP = m_target->GetPos() - a->GetPos();
		CVector3 toPNorm = toP;
		toPNorm.Normalize();

		//�v���C���[�Ƀ_���[�W
		damageCool -= GameTime::GetDeltaTime();

		if(damageCool <= 0 && toP.LengthSq() < pow2( 80 ) && toP.y < 20){
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

}