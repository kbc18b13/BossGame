#include "stdafx.h"
#include "SkyBox.h"
#include "graphics/RenderObjectManager.h"

void SkyBox::Init( const wchar_t* modelPath ){
	m_model.Init( modelPath );

	//非深度書き込みステート
	{
		D3D11_DEPTH_STENCIL_DESC desc{};
		desc.DepthEnable = true;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

		desc.StencilEnable = true;
		desc.StencilWriteMask = 0xff;
		desc.StencilReadMask = 0xff;
		desc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;
		desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		desc.BackFace = desc.FrontFace;
		desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

		g_graphicsEngine->GetD3DDevice()->CreateDepthStencilState( &desc, &m_depthState );
	}

	g_ROManager.AddSkyRender( this );
}

void SkyBox::Render(){
	auto dc = g_graphicsEngine->GetD3DDeviceContext();

	dc->OMSetDepthStencilState( m_depthState.Get(), 0 );

	CMatrix mat = m_model.GetWorldMatrix();
	mat.v[3] = CVector4(g_camera3D.GetPosition(), 1);
	m_model.UpdateWorldMatrix( mat );

	m_model.Draw( EnRenderMode::Sky, g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix() );
}

void SkyBox::SetRot( const CQuaternion & rot ){
	CMatrix mat = m_model.GetWorldMatrix();
	CMatrix rMat;
	rMat.MakeRotationFromQuaternion( rot );
	mat.Mul(mat, rMat );
	m_model.UpdateWorldMatrix( mat );
}
