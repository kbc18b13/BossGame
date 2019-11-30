#include "stdafx.h"
#include "Camera.h"

Camera g_camera3D;		//3D�J�����B

void Camera::Init() {
	m_cbuffer.Init(sizeof(CVector3) + 4, false, &m_position);
	m_cbuffer.SetToContext(ShaderType::PS, 3);
}

void Camera::Update()
{
	//�r���[�s����v�Z�B
	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);
	//�v���W�F�N�V�����s����v�Z�B
	m_projMatrix.MakeProjectionMatrix(
		m_viewAngle,					//��p�B
		FRAME_BUFFER_W / FRAME_BUFFER_H,	//�A�X�y�N�g��B
		m_near,
		m_far
	);
	m_cbuffer.UpdateData(&m_position);
}