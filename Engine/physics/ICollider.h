/*!
 * @brief	�R���C�_�[�B
 */

#pragma once

class btCollisionShape;

/*!
 * @brief	�R���C�_�[�̃C���^�[�t�F�[�X�N���X�B
 */
class ICollider {
public:
	virtual void SetLocalScale( const CVector3& scale, btCollisionObject* updateAABB = nullptr ) = 0;
	virtual btCollisionShape* GetBody() const = 0;
};
