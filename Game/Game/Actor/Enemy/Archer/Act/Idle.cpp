#include "stdafx.h"
#include "Idle.h"
#include "..\Archer.h"
#include "Weapon/Arrow.h"

namespace EnemySpace{

void Idle::SubStart( Actor * s ){
	m_model->Play( int( Archer::Anim::Idle ) , 0.2f);
}
void Idle::Update( Actor * s ){
	CVector3 toP = m_target->GetPos() - s->GetPos();

	m_chara->Excecute();

	if( toP.LengthSq() < pow2( 400 ) ){
		CVector3 myPos = s->GetPos();
		myPos.y += s->GetHeight() / 2;
		CVector3 yourPos = m_target->GetPos();
		yourPos.y += m_target->GetHeight() / 2;

		CVector3 v = Arrow::CalcShotVec( myPos, yourPos, 400 );

		if( !v.isZero() ){
			ActEnd( int( Archer::ActE::Shot ) );
		}
	}
}
}