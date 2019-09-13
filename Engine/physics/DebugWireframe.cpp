#include "stdafx.h"
#include "DebugWireframe.h"

struct Vertex {
	CVector3 pos;
	CVector3 col;
};

DebugWireframe::DebugWireframe() {
	D3D11_DEPTH_STENCIL_DESC depthDesc{};
	depthDesc.DepthEnable = true;
	depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	g_graphicsEngine->GetD3DDevice()->CreateDepthStencilState(&depthDesc, &m_depthState);

	D3D11_BUFFER_DESC bufDesc{};
	bufDesc.ByteWidth = sizeof(Vertex) * 2;
	bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	HRESULT hr = g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufDesc, nullptr, &m_vBuf);
	if (FAILED(hr))abort();

	bufDesc.ByteWidth = sizeof(CMatrix);
	bufDesc.CPUAccessFlags = 0;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	hr = g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufDesc, nullptr, &m_cBuf);
	if (FAILED(hr))abort();

	m_vShader.Load("Assets/shader/DebugWire.fx", "VSMain", Shader::EnType::VS);
	m_pShader.Load("Assets/shader/DebugWire.fx", "PSMain", Shader::EnType::PS);
}

DebugWireframe::~DebugWireframe() {
	m_vBuf->Release();
	m_cBuf->Release();
}

void DebugWireframe::DrawBegin() {
	ID3D11DeviceContext* dc = g_graphicsEngine->GetD3DDeviceContext();
	dc->OMSetDepthStencilState(m_depthState, 0);

	UINT stride = sizeof(Vertex);
	UINT zero = 0;
	dc->IASetVertexBuffers(0, 1, &m_vBuf, &stride, &zero);
	dc->IASetInputLayout(m_vShader.GetInputLayout());
	dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	CMatrix vpMat;
	vpMat.Mul(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());

	dc->UpdateSubresource(m_cBuf, 0, nullptr, &vpMat, 0, 0);

	dc->VSSetConstantBuffers(0, 1, &m_cBuf);
	dc->VSSetShader((ID3D11VertexShader*)m_vShader.GetBody(), nullptr, 0);
	dc->PSSetShader((ID3D11PixelShader*)m_pShader.GetBody(), nullptr, 0);
}

void DebugWireframe::drawLine(const btVector3 & from, const btVector3 & to, const btVector3 & color) {
	ID3D11DeviceContext* dc = g_graphicsEngine->GetD3DDeviceContext();

	D3D11_MAPPED_SUBRESOURCE mapRes;
	dc->Map(m_vBuf, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapRes);

	Vertex* vecMapRes = (Vertex*)mapRes.pData;
	vecMapRes[0].pos = from;
	vecMapRes[0].col = color;
	vecMapRes[1].pos = to;
	vecMapRes[1].col = color;

	dc->Unmap(m_vBuf, 0);

	dc->Draw(2, 0);
}