#pragma once
#include "graphics/SkinModelRender.h"
#include "physics/BoxCollider.h"
#include "ActorHitCollision.h"

class Actor;

class Arrow : public IGameObject{
public:
	Arrow();
	~Arrow();

	void Init(Actor* a);

	static CVector3 CalcShotVec(const CVector3& start, const CVector3& target, float speed);

	void Shot( const CVector3& start, const CVector3& target, float speed ){
		m_vec = CalcShotVec(start, target, speed);
		SetPos( start );
	}

	void Shot( const CVector3& start, const CVector3& vec ){
		m_vec = vec;
		SetPos( start );
	}

	void Update();

	CVector3 GetPos() const{
		return m_model.GetPos();
	}

	CQuaternion GetRot() const{
		return m_model.GetRot();
	}

	void SetPos( const CVector3& pos ){
		m_model.SetPos( pos );
		CVector3 offset = m_colOffset;
		GetRot().Multiply( offset );
		m_collision.SetPos( pos + offset );
	}

	void SetRot( const CQuaternion& rot ){
		m_model.SetRot( rot );
		m_collision.SetRot( rot );
	}

private:
	Actor* owner;
	BoxCollider		m_collider;
	CVector3 m_colOffset = { 0, 0, 13 };
	ActorHitCollision m_collision;
	SkinModelRender m_model;
	static constexpr float m_gravity = 400;
	CVector3 m_vec;
};

