#pragma once
#include "CollisionModel.h"

class ClearDoor{
public:
	ClearDoor( const wchar_t* path ) : m_colModel(path, nullptr, btCollisionObject::CF_Ground, true){

	}

	void SetPos( const CVector3& pos ){
		m_colModel.SetPos( pos );
	}

	void StartClear(){
		m_clearStart = true;
		m_colModel.SetAllowCollision( false );
	}

	void Update();

private:
	bool m_clearStart = false;
	static constexpr float c_clearTime = 4.0f;
	float m_clearTime = c_clearTime;

	CollisionModel m_colModel;
};

