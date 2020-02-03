#include "stdafx.h"
#include "BigDoor.h"

BigDoor::BigDoor() : m_doorL( L"Assets/modelData/BigDoor.cmo" ),
						m_doorR( L"Assets/modelData/BigDoor.cmo" ){
	m_doorR.SetRot( CQuaternion::CreateRotDeg( CVector3::AxisY(), 180 ) );
}

BigDoor::~BigDoor(){}

void BigDoor::Update(){
	if( m_state == enOpen || m_state == enClose ){

		//I—¹ðŒ
		if( m_state == enOpen && m_rot >= 90 ){
			m_state = enOpened;
			return;
		}
		if( m_state == enClose && m_rot <= 0 ){
			m_state = enClosed;
			return;
		}

		//”à‚ð‰ñ“]‚³‚¹‚é
		float speed = 20;

		if( m_state == enClose ){
			speed *= -1;
		}

		m_rot += GameTime::GetDeltaTime() * speed;

		CQuaternion qL;
		qL.SetRotationDeg( CVector3::AxisY(), -m_rot );

		CQuaternion qR;
		qR.SetRotationDeg( CVector3::AxisY(), m_rot + 180 );

		m_doorL.SetRot( qL );
		m_doorR.SetRot( qR );

		m_doorL.CollideChara();
		m_doorR.CollideChara();
	}
}
