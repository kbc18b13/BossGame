#include "stdafx.h"
#include "Camera.h"

Camera g_camera3D;		//3D�J�����B

void Camera::Init() {
	D3D11_BUFFER_DESC desc{};
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = sizeof(CVector3) + 4;
	desc.CPUAccessFlags = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA data{};
	data.pSysMem = &m_position;

	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc, &data, &m_cbuffer);
	g_graphicsEngine->GetD3DDeviceContext()->PSSetConstantBuffers(3, 1, &m_cbuffer);
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

	g_graphicsEngine->GetD3DDeviceContext()->UpdateSubresource(m_cbuffer, 0, nullptr, &m_position, 0, 0);
}