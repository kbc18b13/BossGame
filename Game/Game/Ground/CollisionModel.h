#pragma once
#include "physics/PhysicsStaticObject.h"
class SkinModelRender;
class CollisionModel {
public:
	CollisionModel(const wchar_t* modelPath, const wchar_t* collisionModelPath = nullptr);
	~CollisionModel();

	void SetPos(const CVector3& pos);

	CVector3 GetPos(){
		return m_model.GetPos();
	}

	void SetRot( const CQuaternion& rot );

	void SetScale( const CVector3& scale );

	/// <summary>
	/// �L�����R���̂߂荞�݂���������
	/// </summary>
	void CollideChara();

private:
	SkinModelRender m_model;
	PhysicsStaticObject m_collider;
};