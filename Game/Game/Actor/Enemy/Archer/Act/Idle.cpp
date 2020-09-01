#include "stdafx.h"
#include "Idle.h"
#include "..\Archer.h"

namespace EnemySpace{

void Idle::SubStart( Actor * s ){
	m_model->Play( int( Archer::Anim::Idle ) , 0.2f);
}
void Idle::Update( Actor * s ){
	CVector3 toP = m_target->GetPos() - s->GetPos();

	m_chara->Excecute();

	if( toP.LengthSq() < pow2( 400 ) ){
		ActEnd( int( Archer::ActE::Shot ) );
	}
}
}