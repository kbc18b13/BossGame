#include "stdafx.h"
#include "Shot.h"
#include "..\Archer.h"
#include "Weapon/Arrow.h"

namespace EnemySpace{

void Shot::SubStart( Actor * s ){
	m_model->Play( int( Archer::Anim::Shot ) , 0.3f, true);

	m_model->AddEventFunc( "Shot", [&](){
		CVector3 myPos = s->GetPos();
		myPos.y += s->GetHeight() / 2;
		CVector3 yourPos = m_target->GetPos();
		yourPos.y += m_target->GetHeight() / 2;

		CVector3 v = Arrow::CalcShotVec( myPos, yourPos, 400 );

		if( v.isZero() ){
			ActEnd( int( Archer::ActE::Idle ) );
			return;
		}

		auto arrow = NewGO<Arrow>( 0 );
		arrow->Init(s);

		arrow->Shot( myPos, v );
	} );
}

void Shot::Update( Actor * s ){
	CVector3 toP = m_target->GetPos() - s->GetPos();

	if( toP.LengthSq() > pow2( 400 )){
		ActEnd( int( Archer::ActE::Idle ) );
	}

	m_chara->Excecute();

	toP.y = 0;

	m_model->AddRot( Util::LookRotSLerp( toP, m_model->GetFront(), 0.8f) );

	if( !m_model->IsPlaying() ){
		m_model->Play( int( Archer::Anim::Shot), 0.3f , true );
	}
}
}