#include "stdafx.h"
#include "ModelArmWeapon.h"
#include "graphics/SkinModelRender.h"
#include "physics/CollisionAttr.h"
#include "Actor/Actor.h"


ModelArmWeapon::ModelArmWeapon(){}

ModelArmWeapon::~ModelArmWeapon(){}

void ModelArmWeapon::Init( Bone* handBone, Actor* master, const CVector3& halfExtents,
					  const wchar_t* modelpath, bool playersModelArmWeapon ){
	m_model.Init( modelpath );

	m_collider.Create( halfExtents );

	EnCollisionAttr target = playersModelArmWeapon ? enCollisionAttr_Enemy : enCollisionAttr_Player;

	m_weapon.Init( master, m_collider, target );

	m_hand = handBone;
}

void ModelArmWeapon::Update(){
	m_weapon.UpdateWorldMatrix( m_hand->GetWorldMatrix() );
	m_weapon.Update();
	m_model.SetWorldMatrix( m_hand->GetWorldMatrix() );
	m_model.Update();
}
