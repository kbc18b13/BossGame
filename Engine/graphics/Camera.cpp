#include "stdafx.h"
#include "Camera.h"

Camera g_camera3D;		//3Dカメラ。

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
	//ビュー行列を計算。
	m_viewMatrix.MakeLookAt(
		m_position,
		m_target,
		m_up
	);
	//プロジェクション行列を計算。
	m_projMatrix.MakeProjectionMatrix(
		m_viewAngle,					//画角。
		FRAME_BUFFER_W / FRAME_BUFFER_H,	//アスペクト比。
		m_near,
		m_far
	);

	g_graphicsEngine->GetD3DDeviceContext()->UpdateSubresource(m_cbuffer, 0, nullptr, &m_position, 0, 0);
}