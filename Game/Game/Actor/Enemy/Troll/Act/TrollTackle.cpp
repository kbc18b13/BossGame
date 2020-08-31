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
	//プレイヤーへ向かうベクトル
	CVector3 move = m_target->GetPos() - m_chara->GetPosition();
	move.y = 0;

	//準備中。
	if( !m_isRun && m_model->GetAnim().IsPlaying() ){
		m_chara->Excecute();
		m_model->SetRot( Util::LookRotXZ( move ) );
		return;
	}
	
	//走り出し。
	if( !m_model->GetAnim().IsPlaying() ){
		m_model->Play( int( AnimState::Tackle ), 0.2f );
		bodyCol.StartAttack();
		playerVec = move;
		playerVec.Normalize();
		m_isRun = true;
	}

	//移動
	m_model->SetPos( m_chara->Excecute( playerVec, 4, 0.5f, false ) );
	m_model->SetRot( Util::LookRotXZ( playerVec ) );

	//タイマーが0を下回ったら終了
	if( m_timer <= 0 ){
		bodyCol.EndAttack();
		ActEnd( int( ActState::Wait ));
	} else{
		m_timer -= GameTime::GetDeltaTime();
	}
}

}
