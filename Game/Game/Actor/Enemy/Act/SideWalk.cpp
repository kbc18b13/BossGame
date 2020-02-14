#include "stdafx.h"
#include "SideWalk.h"
#include "Actor/Actor.h"

EnemySpace::SideWalk::SideWalk( int walkAnim, int nextState ) : m_walkAnim(walkAnim), m_nextState(nextState){}

EnemySpace::SideWalk::~SideWalk(){}

void EnemySpace::SideWalk::SubStart( Actor * a ){
	m_timer = 4;
}

void EnemySpace::SideWalk::Update( Actor * a ){
	CVector3 toP = m_target->GetPos() - m_chara->GetPosition();

	//遠ければやめる。時間切れでもやめる。
	if( toP.LengthSq() > pow2( 100 ) || m_timer < 0){
		ActEnd( m_nextState );
		return;
	}

	//モデルのアニメーションと向きの設定
	m_model->Play( m_walkAnim, 0.2f );
	m_model->SetRot(Util::LookRotXZ(toP));

	//横に向かって歩かせる
	CVector3 walk = toP;
	CQuaternion::CreateRotDeg( CVector3::AxisY(), 90 ).Multiply( walk );
	m_chara->Excecute( walk, 0.2f, 1, false );

	m_timer -= GameTime::GetDeltaTime();
}
