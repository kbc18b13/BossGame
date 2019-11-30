#include "stdafx.h"
#include "Sprite.h"

/// <summary>
/// SpriteÇÃí∏ì_
/// </summary>
struct SpriteVertex {
	CVector3 pos;
	CVector2 uv;
};

Sprite::Sprite() {
}


Sprite::~Sprite() {
	m_vertex->Release();
}

void Sprite::Init(const wchar_t * path, UINT width, UINT height) {
	HRESULT result;

    m_width = width;
    m_height = height;

	int w = width / 2;
	int h = height / 2;

	SpriteVertex vertexData[4]{
		{CVector3( w, h, 0.0f),CVector2(1,0) },
		{CVector3(-w, h, 0.0f),CVector2(0,0) },
		{CVector3( w,-h, 0.0f),CVector2(1,1) },
		{CVector3(-w,-h, 0.0f),CVector2(0,1) },
	};

	D3D11_BUFFER_DESC desc{};
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = sizeof(vertexData);
	desc.CPUAccessFlags = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA data{};
	data.pSysMem = vertexData;
	

	result = g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc, &data, &m_vertex);

	if (FAILED(result)) {
		abort();
	}

	m_effect.loadTexture(path);

	if (FAILED(result)) {
		abort();
	}

	m_worldMat.MakeScaling({ 1 / FRAME_BUFFER_W, 1 / FRAME_BUFFER_H, 1 });
	m_worldMatBuf.Init( sizeof( CMatrix ), false , &m_worldMat);
}

void Sprite::Draw() {
	UINT zero = 0;
	UINT stride = sizeof(SpriteVertex);
	ID3D11DeviceContext* context = g_graphicsEngine->GetD3DDeviceContext();
	m_effect.Apply(context);
	context->IASetVertexBuffers(0, 1, &m_vertex, &stride, &zero);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_worldMatBuf.SetToContext( ShaderType::VS, 0 );
	context->Draw(4, 0);
}

void Sprite::UpdateWorldMatrix(const CVector2 & pos, const CVector2 & scale, const CQuaternion & rot) {
	CMatrix scaleMat;
	scaleMat.MakeScaling({scale.x, scale.y, 1});
	CMatrix rotMat;
	rotMat.MakeRotationFromQuaternion(rot);
	CMatrix posMat;
	posMat.MakeTranslation({ pos.x, pos.y, 0 });

	m_worldMat.Mul(scaleMat, rotMat);
	m_worldMat.Mul(m_worldMat, posMat);

	CMatrix projMat;//x -1 Å` 1, y -1 Å` 1ÇÃ2*2XYïΩñ Ç…é˚ÇﬂÇÈÇΩÇﬂÇÃçsóÒ
	projMat.MakeScaling({ 2 / FRAME_BUFFER_W, 2 / FRAME_BUFFER_H, 1 });

	m_worldMat.Mul(m_worldMat, projMat);

	m_worldMatBuf.UpdateData( &m_worldMat );
}
