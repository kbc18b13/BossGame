#pragma once
#include "CollisionModel.h"
class BigDoor : public IGameObject{
public:
	BigDoor();
	~BigDoor();

	void Update() override;

	void SetPos( const CVector3& pos ){
		m_doorL.SetPos( pos );
		m_doorR.SetPos( pos + CVector3::AxisX() * 115 );
	}

	void Open(){
		m_state = enOpen;
	}

	void Close(){
		m_state = enClose;
	}

	void SetStencilRef(int ref){
		m_doorL.GetModel()->GetModel().SetStencilRef( ref );
		m_doorR.GetModel()->GetModel().SetStencilRef( ref );
	}

private:
	CollisionModel m_doorL;
	CollisionModel m_doorR;

	float m_rot = 0;

	enum State{
		enClosed,
		enOpened,
		enClose,
		enOpen,
	};
	State m_state = enClosed;
};

