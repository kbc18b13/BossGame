/*!
 * @brief	静的オブジェクト。
 */

#pragma once

#include "physics/MeshCollider.h"
#include "physics/RigidBody.h"


/*!
* @brief	静的物理オブジェクト
*/
class PhysicsStaticObject{
public:
	/*!
		* @brief	コンストラクタ。
		*/
	PhysicsStaticObject();
	/*!
		* @brief	デストラクタ。
		*/
	~PhysicsStaticObject();
	/*!
		* @brief	メッシュの静的オブジェクトを作成。
		*@param[in]	skinModel	スキンモデル。
		*@param[in]	pos			座標。
		*@param[in]	rot			回転。
		*/
	void CreateMeshObject( SkinModel& skinModel,const CVector3& pos,const CQuaternion& rot ){
		//メッシュコライダーを作成。
		m_meshCollider.CreateFromSkinModel( skinModel );
		CreateRigidBody( pos, rot );
	}

	void CreateMeshObject( const wchar_t* modelPath, const CVector3& pos, const CQuaternion& rot ){
		//メッシュコライダーを作成。
		m_meshCollider.CreateFromCMOFile( modelPath );
		CreateRigidBody( pos, rot );
	}
	
	//位置を設定
	void SetPos(const CVector3& pos) {
		btTransform trans = m_rigidBody.GetBody()->getWorldTransform();
		trans.setOrigin(pos.toBT() );
		m_rigidBody.GetBody()->setWorldTransform(trans);
	}

	void SetRot( const CQuaternion& rot ){
		btTransform trans = m_rigidBody.GetBody()->getWorldTransform();
		trans.setRotation( rot.toBT() );
		m_rigidBody.GetBody()->setWorldTransform( trans );
	}

	void SetScale( const CVector3& scale ){
		m_meshCollider.SetLocalScale( scale , m_rigidBody.GetBody());
	}

	MeshCollider* GetShape(){
		return &m_meshCollider;
	}

	RigidBody* GetRigidBody(){
		return &m_rigidBody;
	}

	void SetFlag( btCollisionObject::CollisionFlags flag ){
		m_flag = flag;
	}

	void SetActive( bool active );

private:
	void CreateRigidBody( CVector3 pos, CQuaternion rot );

	bool m_isActive = true;
	MeshCollider m_meshCollider;		//!<メッシュコライダー。
	RigidBody m_rigidBody;				//!<剛体。
	btCollisionObject::CollisionFlags m_flag;
};
