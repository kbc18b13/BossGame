#pragma once
#include "physics/PhysicsStaticObject.h"
class SkinModelRender;
class CollisionModel {
public:
	CollisionModel(const wchar_t* modelPath, const wchar_t* collisionModelPath = nullptr,
					btCollisionObject::CollisionFlags flag = btCollisionObject::CF_Ground ,
					bool alpha = false);
	~CollisionModel();

	void SetPos(const CVector3& pos);

	CVector3 GetPos(){
		return m_model.GetPos();
	}

	void SetRot( const CQuaternion& rot );

	void SetScale( const CVector3& scale );

	void SetAllowCollision( bool allow ){
		m_collider.SetActive( allow );
	}

	SkinModelRender* GetModel(){
		return &m_model;
	}

	void SetUserIndex(EnCollisionAttr index){
		m_collider.SetUserIndex( index );
	}

	/// <summary>
	/// キャラコンのめり込みを解決する
	/// </summary>
	void CollideChara();

private:
	SkinModelRender m_model;
	PhysicsStaticObject m_collider;
};