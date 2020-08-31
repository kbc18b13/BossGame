#include "stdafx.h"
#include "TrollTackle.h"
#include "graphics/SkinModelRender.h"
#include "Actor/Player/Player.h"
#include "Scene/Stage1.h"
#include "..\Troll.h"
using AnimState = Troll::AnimState;
using ActState = Troll::ActState;

namespace EnemySpace{

TrollTackle::TrollTackle( TrollBodyCollision& body ) : bodyCol( body ){

}

void TrollTackle::SubStart( Actor* t ){
	m_model->Play( int( AnimState::PrepareTackle ), 0.2f );
	m_isRun = false;
	m_timer = 2;
}

void TrollTackle::Update( Actor* t ){
	//�v���C���[�֌������x�N�g��
	CVector3 move = m_target->GetPos() - m_chara->GetPosition();
	move.y = 0;

	//�������B
	if( !m_isRun && m_model->GetAnim().IsPlaying() ){
		m_chara->Excecute();
		m_model->SetRot( Util::LookRotXZ( move ) );
		return;
	}
	
	//����o���B
	if( !m_model->GetAnim().IsPlaying() ){
		m_model->Play( int( AnimState::Tackle ), 0.2f );
		bodyCol.StartAttack();
		playerVec = move;
		playerVec.Normalize();
		m_isRun = true;
	}

	//�ړ�
	m_model->SetPos( m_chara->Excecute( playerVec, 4, 0.5f, false ) );
	m_model->SetRot( Util::LookRotXZ( playerVec ) );

	//�^�C�}�[��0�����������I��
	if( m_timer <= 0 ){
		bodyCol.EndAttack();
		ActEnd( int( ActState::Wait ));
	} else{
		m_timer -= GameTime::GetDeltaTime();
	}
}

}
