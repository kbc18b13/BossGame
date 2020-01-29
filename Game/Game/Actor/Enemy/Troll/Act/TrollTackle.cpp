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
	bodyCol.StartAttack();
	playerPos = m_target->GetPos();
	m_timer = 8.0f;
}

void TrollTackle::Update( Actor* t ){
	//�v���C���[�֌������đ��点��
	CVector3 move = playerPos - m_chara->GetPosition();

	move.y = 0;
	float moveLength = move.Length();

	if(moveLength < 10 ){
		m_timer = 0;
	}

	move /= moveLength;
	move *= 5;

	m_model->Play( int( AnimState::Tackle ), 0.2f );
	m_model->SetPos( m_chara->Excecute( move, 4, 0.5f, false ) );
	m_model->SetRot( Util::LookRotXZ( move ) );

	//�^�C�}�[��0�����������I��
	if( m_timer <= 0 ){
		bodyCol.EndAttack();
		ActEnd( int( ActState::Wait ));
	} else{
		m_timer -= GameTime::GetDeltaTime();
	}
}

}
