/*!
 * @brief	カプセルコライダー。
 */

#pragma once

#include "Physics/ICollider.h"


class BoxCollider : public ICollider
{
public:
	/*!
	* @brief	デストラクタ。
	*/
	~BoxCollider();
	
	/// <summary>
	/// 作成。
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
private:
	btBoxShape* shape = nullptr;
};
