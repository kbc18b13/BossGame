#include "stdafx.h"
#include "TrollBodyCollision.h"
#include "Troll.h"

TrollBodyCollision::TrollBodyCollision(){}

TrollBodyCollision::~TrollBodyCollision(){}

void TrollBodyCollision::Init( Troll * troll){
	m_shape.Create(45, 40);
	m_collision.Init( m_shape, EnCollisionAttr::enCollisionAttr_Player, troll );
	m_collision.SetOffset( CVector3( 0, 40, 0 ) );
	m_master = troll;
}

void TrollBodyCollision::Update(){
	if( !isAttack ){
		return;
	}
	//�ʒu�X�V
	m_collision.SetPos( m_master->GetPos() );

	//�ڐG�e�X�g
	std::vector<Actor*> hits = m_collision.ContactTest();
	CVector3 pos = m_master->GetPos();
	for( Actor* a : hits ){
		if( a->Damage( damage, coolTime, m_master ) ){
			CVector3 v = a->GetPos() - pos;
			v.y = 0;
			v.Normalize();
			v *= 1500;
			v.y = 200;
			a->AddVelocity( v );
		}
	}
}
