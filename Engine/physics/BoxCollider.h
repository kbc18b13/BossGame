/*!
 * @brief	�J�v�Z���R���C�_�[�B
 */

#pragma once

#include "Physics/ICollider.h"


class BoxCollider : public ICollider
{
public:
	/*!
	* @brief	�f�X�g���N�^�B
	*/
	~BoxCollider();
	
	/// <summary>
	/// �쐬�B
	/// </summary>
	/// <param name="radius"></param>
	/// <param name="height"></param>
	void Create(const btVector3& halfExtents)
	{
		shape = new btBoxShape(halfExtents);
	}
	btCollisionShape* GetBody() const override
	{
		return shape;
	}

	void SetLocalScale( const CVector3& scale, btCollisionObject* updateAABB = nullptr ) override{
		shape->setLocalScaling( scale );
		if( updateAABB ) g_physics.UpdateSingleAABB( updateAABB );
	}

private:
	btBoxShape* shape = nullptr;
};
