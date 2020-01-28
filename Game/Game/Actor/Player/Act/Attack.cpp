#include "stdafx.h"
#include "Attack.h"

namespace PlayerAct{

Attack::Attack( Player::Anim animation_, Player::Anim nextAttack_ ){
	animation = animation_;
	nextAttack = nextAttack_;
	m_needStamina = 5;
}


Attack::~Attack(){}

void Attack::SubStart( Actor* p ){
	m_sword->AttackStart();
	pushedAtkButton = false;
	m_timer = 0;
}

void Attack::Update( Actor* p ){
	//回避
	if( g_pad->IsTrigger( enButtonB ) ){
		m_sword->AttackEnd();
		ActEnd( int(Player::Anim::Roll) );
		return;
	}

	//攻撃ボタンを押したら、次の遷移先はコンボ攻撃
	if( g_pad->IsTrigger( enButtonRB1 ) ){
		pushedAtkButton = true;
	}

	//コンボ可能な時間
	if( m_timer > 0.3f ){
		if( nextAttack != Player::Anim::SlashEnd && pushedAtkButton ){
			
			if( ChangeAct( p, nextAttack ) ){
				return;
			}
		}
	}

	//アニメーション終了後は遷移
	if( !m_model->IsPlaying() ){
		sword( p ).AttackEnd();
		ChangeActDefault( p );
	}

	m_model->Play( int( animation ), 0.2f );
	m_chara->Excecute();
	m_timer += GameTime::GetDeltaTime();
}

}