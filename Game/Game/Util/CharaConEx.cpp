#include "stdafx.h"
#include "CharaConEx.h"

void CharaConEx::Init( const CharaConDesc& desc ){
	m_charaCon.Init( desc.radius, desc.height, desc.position, desc.userIndex, desc.userPointer );
	m_walkAccel = desc.walkAccel;
	m_walkAccelAir = desc.walkAccelAir;
	m_walkMax = desc.walkMax;
	m_jumpPower = desc.jumpPower;
	m_gravity = desc.gravity;
}

CVector3 CharaConEx::Excecute( const CVector3& _pad, float speedScale, float accelScale, bool jump ){
	CVector2 pad( _pad.x, _pad.z );
	if( pad.LengthSq() > 0.001f ){
		pad.Normalize();
	}

	//���s
	{
		//�󒆂Ɛڒn�ŃX�s�[�h�𕪂���
		const float accel = ( m_charaCon.IsOnGround() ? m_walkAccel : m_walkAccelAir ) *accelScale;
		const float maxSpeed = m_walkMax * speedScale;
		//���݂̑��x���}�C�i�X�ɂ��ė^���邱�ƂŁA�ő呬�x�ɋ߂��قǉ���������������B
		//_____________________�ő呬�x___________���݂̑��x___________�f���^�^�C��_______�����X�s�[�h
		m_moveSpeedXZ += ( ( pad * maxSpeed ) - m_moveSpeedXZ ) * GameTime::GetDeltaTime() * accel;

		if( m_timeMoveTime > 0 ){
			m_moveSpeedXZ = m_timeMoveVec.xz();
		}

	}

	//�㉺
	{
		m_jumpSpeed -= m_gravity * GameTime::GetDeltaTime();
		if( jump && m_charaCon.IsOnGround() ){
			m_jumpSpeed += m_jumpPower;
		}
		if( m_timeMoveTime > 0 ){
			m_jumpSpeed += m_timeMoveVec.y;
			m_timeMoveTime -= GameTime::GetDeltaTime();
		}
	}

	CVector3 prop( m_moveSpeedXZ.x, m_jumpSpeed, m_moveSpeedXZ.y );
	m_charaCon.Execute( GameTime::GetDeltaTime(), prop );
	m_jumpSpeed = prop.y;
	return m_charaCon.GetPosition();
}
