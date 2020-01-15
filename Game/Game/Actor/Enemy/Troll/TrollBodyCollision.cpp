#include "stdafx.h"
#include "TrollBodyCollision.h"
#include "Troll.h"

TrollBodyCollision::TrollBodyCollision(){}

TrollBodyCollision::~TrollBodyCollision(){}

void TrollBodyCollision::Init( Troll * troll){
	m_shape.Create(60, 40);
	m_collision.Init( m_shape, EnCollisionAttr::enCollisionAttr_Player, troll );
	m_collision.SetOffset( CVector3( 0, 10, 0 ) );
	m_master = troll;
}

void TrollBodyCollision::Update(){
	if( !isAttack ){
		return;
	}
	//位置更新
	m_collision.SetPos( m_master->GetPos() );

	//接触テスト
	std::vector<Actor*> hits = m_collision.ContactTest();
	CVector3 pos = m_master->GetPos();
	for( Actor* a : hits ){
		if( a->Damage( damage, coolTime, m_master ) ){
			CVector3 v = a->GetPos() - pos;
			v.y = 0;
			v.Normalize();
			v *= 1000;
			v.y = 100;
			a->AddVelocity( v );
		}
	}
}
