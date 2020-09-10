#include "stdafx.h"
#include "OnLadder.h"
#include "Ground/Ladder.h"

static float ladderSpeed = 3;

PlayerSpace::OnLadder::OnLadder(){}

PlayerSpace::OnLadder::~OnLadder(){}

void PlayerSpace::OnLadder::SubStart( Actor * p ){
	state = Grip;
	oriru = false;
	isUp = true;
	gripTime = 0.0f;

	firstPos = p->GetPos();
	firstRot = p->GetRot();

	toPos = m_ladder->GetPos();
	toPos.y = std::min(p->GetPos().y, m_ladder->GetPos().y + Ladder::Height - 10);
	toPos += m_ladder->GetFront() * 10;

	toRot = m_ladder->GetRot();
	toRot.AddRotationDeg( CVector3::AxisY(), 180 );

	m_chara->SetVelocity( CVector3::Zero() );

	m_model->Play( int( Player::Anim::OnLadder ));
	m_model->SetAnimSpeed( 0 );
}

void PlayerSpace::OnLadder::Update( Actor * p ){
	gripTime += GameTime::GetDeltaTime();

	//‚Í‚µ‚²‚É•ß‚Ü‚é‚Ü‚ÅB
	if( state == Grip ){
		CQuaternion rot;
		rot.Slerp( gripTime / c_gripTime, firstRot, toRot );
		CVector3 pos;
		pos.Lerp( gripTime / c_gripTime, firstPos, toPos );

		p->SetPos( pos );
		p->SetRot( rot );
		if( gripTime > c_gripTime ){
			p->SetRot( toRot );
			p->SetPos( toPos );
			state = Climb;
		} else{
			return;
		}
	}

	//‚Í‚µ‚²‚ð“o‚Á‚Ä‚¢‚éÅ’†
	if( state == Climb ){
		float stickY = g_pad->GetLStickYF();
		if( isUp && stickY < 0 ){
			m_model->Play( int( Player::Anim::OnLadder ), 0.3f, true, true );
			isUp = false;
		}
		if( !isUp && stickY > 0 ){
			m_model->Play( int( Player::Anim::OnLadder ), 0.3f, true, false );
			isUp = true;
		}

		p->SetPos( p->GetPos() + CVector3::Up() * ladderSpeed * stickY );
		m_model->SetAnimSpeed( std::fabsf(stickY) );
		float nowHeight = p->GetPos().y - m_ladder->GetPos().y;

		if( nowHeight <= 5 ){
			oriru = true;
		}

		if( nowHeight >= Ladder::Height ){
			state = GetOff;
			gripTime = 0;
			toPos = firstPos = p->GetPos();
			firstRot = p->GetRot();
			toPos += m_ladder->GetFront() * -20;
		}
	}

	//‚Í‚µ‚²‚ð—£‚µ‚Ä~‚è‚é‚Æ‚«
	if( state == GetOff ){
		m_model->Play( int( Player::Anim::Idle ) , 0.2f);

		CQuaternion rot;
		rot.Slerp( gripTime / c_gripTime, firstRot, toRot );
		CVector3 pos;
		pos.Lerp( gripTime / c_gripTime, firstPos, toPos );

		p->SetPos( pos );
		p->SetRot( rot );

		if( gripTime > c_gripTime ){
			p->SetRot( toRot );
			p->SetPos( toPos );
			oriru = true;
		}
	}


	if( oriru )
		ActEnd( int( Player::Act::Walker ) );

	if( g_pad->IsTrigger( enButtonA ) ){
		oriru = true;
		m_model->Play( int( Player::Anim::Jump ) );
		m_model->SetAnimSpeed( 1.0f );
		m_chara->AddVelocity( CVector3::Up() * 500 );
	}                                                                                                                                                                                                                                                                                
}

void PlayerSpace::OnLadder::End( Actor * p ){
	m_model->SetAnimSpeed( 1.0f );
}
