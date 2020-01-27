#include "stdafx.h"
#include "ArmWeapon.h"
#include "graphics/SkinModelRender.h"
#include "physics/CollisionAttr.h"
#include "Actor/Actor.h"


ArmWeapon::ArmWeapon(){}

ArmWeapon::~ArmWeapon(){
}

void ArmWeapon::Init( Bone* handBone, Actor* master , const CVector3& halfExtents,bool playersArmWeapon){

    m_collider.Create( halfExtents );

	EnCollisionAttr target = playersArmWeapon ? enCollisionAttr_Enemy : enCollisionAttr_Player;

	m_weapon.Init( master, m_collider, target);

    m_hand = handBone;
}

void ArmWeapon::Update(){
	m_weapon.UpdateWorldMatrix( m_hand->GetWorldMatrix() );
	m_weapon.Update();
}
