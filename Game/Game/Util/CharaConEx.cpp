#include "stdafx.h"
#include "CharaConEx.h"

void CharaConEx::Init(const CharaConDesc& desc) {
	m_charaCon.Init(desc.radius, desc.height, desc.position, desc.userIndex, desc.userPointer);
	m_walkAccel    = desc.walkAccel;
	m_walkAccelAir = desc.walkAccelAir;
	m_walkBrake    = desc.walkBrake;
	m_walkMax      = desc.walkMax;
	m_jumpPower    = desc.jumpPower;
	m_gravity      = desc.gravity;
}

CVector3 CharaConEx::Excecute(const CVector2& pad, bool jump) {
	//���s
	{
		//�󒆂Ɛڒn�ŃX�s�[�h�𕪂���
		const float accel = m_charaCon.IsOnGround() ? m_walkAccel : m_walkAccelAir;

		//�ő呬�x�B�O���ɂ����WALK_MAX�𒴉߂��Ă���ꍇ�A�����W���Ȃ��B
		const float maxSpeed = max(m_walkMax, m_moveSpeedXZ.Length());

		//��������
		m_moveSpeedXZ += pad * accel;

		const float len = m_moveSpeedXZ.Length();//�ړ��x�N�g���̒���

		if (len > 0.1f) {//��~���Ă��Ȃ��ꍇ

			//��������
			CVector2 norm = m_moveSpeedXZ / len;
			CVector2 beforeSpeed = m_moveSpeedXZ;
			m_moveSpeedXZ -= norm * m_walkBrake;
			if (m_moveSpeedXZ.Dot(beforeSpeed) < 0) {//�����̌��ʋt�����ɍs�������~����B
				m_moveSpeedXZ = CVector2(0, 0);
			}


			if (len > maxSpeed) {//����ȏ�̃X�s�[�h���o�Ă���Ȃ�}����B
				m_moveSpeedXZ /= len;
				m_moveSpeedXZ *= maxSpeed;
			}
		}
	}

	//�㉺
	{
		m_jumpSpeed -= m_gravity * GameTime::GetDeltaTime();
		if (jump) {
			m_jumpSpeed += m_jumpPower;
		}
	}

	CVector3 prop(m_moveSpeedXZ.x, m_jumpSpeed, m_moveSpeedXZ.y);
	m_charaCon.Execute(GameTime::GetDeltaTime(), prop);
	m_jumpSpeed = prop.y;
	return m_charaCon.GetPosition();
}
