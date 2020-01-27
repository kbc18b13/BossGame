#include "stdafx.h"
#include "Weapon.h"
#include "Actor/Actor.h"

void Weapon::Init( Actor * master, ICollider & collider, EnCollisionAttr target ){
	m_collision.Init( collider, target, master );
	m_master = master;
}

void Weapon::Update(){
	if( !m_isAttack ){
		return;
	}

	//接触テスト
	std::vector<Actor*> hits = m_collision.ContactTest();
	CVector3 pos = m_master->GetPos();
	for( Actor* a : hits ){

		//既にヒットしたアクターでない場合だけ、ヒット処理を行う。
		if( std::find( m_hitActors.begin(), m_hitActors.end(), a ) == m_hitActors.end() ){
			//ダメージ
			a->Damage( m_damage, m_master );
			//ノックバック
			CVector3 v = a->GetPos() - pos;
			CVector3 knockBack = m_knock;
			Util::LookRotXZ( v ).Multiply(knockBack);
			a->AddVelocity( knockBack );
			//ヒットしたアクターの配列に追加
			m_hitActors.push_back( a );
		}

	}
}

void Weapon::UpdateWorldMatrix( CMatrix mat ){
	CQuaternion rot;
	rot.SetRotation( mat );
	m_collision.SetRot( rot );
	m_collision.SetPos( CVector3( mat.v[3] ) );
}
