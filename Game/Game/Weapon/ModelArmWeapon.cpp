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
	CMatrix mat = m_hand->GetWorldMatrix();
	m_weapon.UpdateWorldMatrix( mat );
	m_weapon.Update();

	CMatrix modelMat;
	modelMat.MakeRotationFromQuaternion( m_modelRot );
	CMatrix offset;
	offset.MakeTranslation( m_modelOffset );

	modelMat.Mul( modelMat, offset );
	modelMat.Mul( modelMat, mat );
	

	m_model.SetWorldMatrix( modelMat);
	m_model.AddRot( m_modelRot );
	m_model.Update();
}
