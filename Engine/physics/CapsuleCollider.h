/*!
 * @brief	カプセルコライダー。
 */

#pragma once

#include "Physics/ICollider.h"


class CapsuleCollider : public ICollider
{
public:
	/*!
	* @brief	デストラクタ。
	*/
	~CapsuleCollider();
	/*!
	* @brief	作成。
	*@param[in] radius	カプセルの半径。
	*@param[in]	height	カプセルの高さ。
	*/
	void Create(float radius, float height)
	{
		shape = new btCapsuleShape(radius, height);
		this->radius = radius;
		this->height = height;
	}
	btCollisionShape* GetBody() const override
	{
		return shape;
	}
	float GetRadius() const
	{
		return radius;
	}
	float GetHeight() const
	{
		return height;
	}

	void SetLocalScale( const CVector3& scale, btCollisionObject* updateAABB = nullptr ) override{
		shape->setLocalScaling( scale.toBT() );
		if( updateAABB ) g_physics.UpdateSingleAABB( updateAABB );
	}

private:
	btCapsuleShape*		shape = nullptr;
	float radius = 0.0f;
	float height = 0.0f;
};
