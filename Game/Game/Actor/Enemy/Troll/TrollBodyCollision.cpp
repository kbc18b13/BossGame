#include "stdafx.h"
#include "TrollBodyCollision.h"
#include "Troll.h"

TrollBodyCollision::TrollBodyCollision(){}

TrollBodyCollision::~TrollBodyCollision(){}

void TrollBodyCollision::Init( Troll * troll){
	m_shape.Create(45, 40);
	m_weapon.Init( troll , m_shape, EnCollisionAttr::enCollisionAttr_Player);
	m_weapon.SetOffset( CVector3( 0, 40, 0 ) );
	m_weapon.SetDamage( 30 );
	m_weapon.SetKnockBack( CVector3( 0, 100, 1000 ) );
	m_master = troll;
}

void TrollBodyCollision::Update(){
	CMatrix mat;
	mat.v[3] = CVector4(m_master->GetPos(), 1);
	m_weapon.UpdateWorldMatrix( mat );
	m_weapon.Update();
}
