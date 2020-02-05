#pragma once
#include "character/CharacterController.h"

struct CharaConDesc {
	float radius = 0;
	float height = 0;

	CVector3 position;

	int userIndex     = enCollisionAttr_Character;
	void* userPointer = nullptr;

	float walkAccel    = 0;
	float walkAccelAir = 0;
	float walkMax      = 0;

	float jumpPower    = 0;
	float gravity      = 0;
};

class CharaConEx {
public:

    /// <summary>
    /// ������
    /// </summary>
    /// <param name="desc">�������p�����[�^</param>
	void Init(const CharaConDesc& desc);

    /// <summary>
    /// �ړ������s����
    /// </summary>
    /// <param name="moveXZ">XZ���ʂ��ړ�</param>
    /// <param name="jump">�W�����v�̗L��</param>
    /// <returns></returns>
	CVector3 Excecute( const CVector3& moveXZ, bool jump ){
		return Excecute( moveXZ, 1, 1, jump );
	}

	CVector3 Excecute( const CVector3& moveXZ, float maxSpeedScale, float accelScale ,bool jump );

	/// <summary>
	/// move�[���Ajump������Execute�B
	/// </summary>
	CVector3 Excecute(){
		return Excecute( CVector3::Zero(), false );
	}

    //�ʒu��ݒ�
	void SetPosition(const CVector3& pos) {
		m_charaCon.SetPosition(pos);
	}

    //�ʒu���擾
	CVector3 GetPosition() const{
		return m_charaCon.GetPosition();
	}

    //���x���擾
	CVector3 GetVelocity() const {
		return CVector3(m_moveSpeedXZ.x, m_jumpSpeed, m_moveSpeedXZ.y);
	}

    //���x��ݒ�
    void SetVelocity(const CVector3& v) {
        m_moveSpeedXZ.x = v.x;
        m_jumpSpeed = v.y;
        m_moveSpeedXZ.y = v.z;
    }

    //����
    void AddVelocity(const CVector3& v) {
        m_moveSpeedXZ.x += v.x;
        m_jumpSpeed += v.y;
        m_moveSpeedXZ.y += v.z;
    }

	//���Ԃƕ��������߂Ĉړ��B
	void Move( const CVector3& v, float time ){
		m_timeMoveVec = v;
		m_timeMoveTime = time;
	}

    //���n���Ă���Ȃ�true
	bool OnGround() const {
		return m_charaCon.IsOnGround();
	}

    //�d�͉����x���擾
    float GetGravity() {
        return m_gravity;
    }

	void SetActive( bool active ){
		m_charaCon.SetActive( active );
	}

	float GetHeight(){
		return m_charaCon.GetHeight();
	}

private:
	float m_walkAccel;
	float m_walkAccelAir;
	float m_walkMax;

	float m_jumpPower;
	float m_gravity;

	CVector2 m_moveSpeedXZ;
	float m_jumpSpeed = 0.0f;

	CVector3 m_timeMoveVec;
	float m_timeMoveTime = 0.0f;

	CharacterController m_charaCon;
};