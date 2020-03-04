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

	//�ڐG�e�X�g
	std::vector<Actor*> hits = m_collision.ContactTest();
	CVector3 pos = m_master->GetPos();
	for( Actor* a : hits ){

		//���Ƀq�b�g�����A�N�^�[�łȂ��ꍇ�����A�q�b�g�������s���B
		if( std::find( m_hitActors.begin(), m_hitActors.end(), a ) == m_hitActors.end() ){
			//�_���[�W
			a->Damage( m_damage, m_master );
			//�m�b�N�o�b�N
			CVector3 v = a->GetPos() - pos;
			CVector3 knockBack = m_knock;
			Util::LookRotXZ( v ).Multiply(knockBack);
			a->AddVelocity( knockBack );
			//�q�b�g�����A�N�^�[�̔z��ɒǉ�
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
