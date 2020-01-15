/*!
 * @brief	�J�v�Z���R���C�_�[�B
 */

#pragma once

#include "Physics/ICollider.h"


class CylinderCollider : public ICollider
{
public:
	/*!
	* @brief	�f�X�g���N�^�B
	*/
	~CylinderCollider();
	
	/// <summary>
	/// �쐬�B
	/// </summary>
	/// <param name="radius"></param>
	/// <param name="height"></param>
	void Create(float height, float radius)
	{
		shape = new btCylinderShape(btVector3(radius, height, radius));
	}
	btCollisionShape* GetBody() const override
	{
		return shape;
	}
private:
	btCylinderShape* shape = nullptr;
};
