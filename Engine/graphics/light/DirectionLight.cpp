#include "stdafx.h"
#include "DirectionLight.h"

DirectionLight::DirectionLight() {
}

DirectionLight::~DirectionLight() {
}

void DirectionLight::Init(UINT bufferNum) {
	D3D11_BUFFER_DESC bDesc{};
	bDesc.ByteWidth = ((sizeof(m_cbStruct) - 1) / 16 + 1) * 16;
	bDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bDesc.Usage = D3D11_USAGE_DEFAULT;
	bDesc.CPUAccessFlags = 0;

	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bDesc, nullptr, &m_CBuf);

	m_bufferNum = bufferNum;
}

void DirectionLight::Apply() {
	g_graphicsEngine->GetD3DDeviceContext()->UpdateSubresource(m_CBuf, 0, nullptr, &m_cbStruct, 0, 0);
	g_graphicsEngine->GetD3DDeviceContext()->PSSetConstantBuffers(m_bufferNum, 1, &m_CBuf);
}
