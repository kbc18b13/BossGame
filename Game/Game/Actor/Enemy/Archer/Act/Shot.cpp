#include "stdafx.h"
#include "Shot.h"
#include "..\Archer.h"

namespace EnemySpace{

void Shot::SubStart( Actor * s ){
	m_model->Play( int( Archer::Anim::Shot ) , 0.1f, true);
}

void Shot::Update( Actor * s ){
	CVector3 toP = m_target->GetPos() - s->GetPos();

	if( toP.LengthSq() > pow2( 400 ) ){
		ActEnd( int( Archer::ActE::Idle ) );
	}

	m_chara->Excecute();

	if( !m_model->IsPlaying() ){
		m_model->Play( int( Archer::Anim::Shot), 0.1f , true );
	}
}
}