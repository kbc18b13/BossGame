#include "stdafx.h"
#include "CascadeShadow.h"
#include "SkinModelRender.h"
#include "SkinModelShaderConst.h"
//SkinModelRender* g_testSk[4] = {};

CascadeShadow::CascadeShadow(){}


CascadeShadow::~CascadeShadow(){}

void CascadeShadow::Init( unsigned int w, unsigned int h ){

	//分割距離を設定
	{
		float partLen = 0.0f;
		int pCount = 0;
		for( auto& p : parts ){
			p.Init( w, h );
			p.SetPart( partLen, partLen + 1.0f / partNum );
			partLen += 1.0f / partNum;

			partFarClips[pCount++] = p.GetCameraFar();
		}
	}

	//サンプラー作成
	{
		D3D11_SAMPLER_DESC sampDesc{};
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
		sampDesc.BorderColor[0] = 1;
		sampDesc.BorderColor[1] = 1;
		sampDesc.BorderColor[2] = 1;
		sampDesc.BorderColor[3] = 1;
		sampDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_LESS;

		HRESULT res = g_graphicsEngine->GetD3DDevice()->CreateSamplerState( &sampDesc, &m_sampler );
		if( FAILED( res ) )abort();
		g_graphicsEngine->GetD3DDeviceContext()->PSSetSamplers( 2, 1, m_sampler.GetAddressOf() );
	}

	//コンストバッファー作成
	{
		shadowVCB.Init( Util::AlignSize( sizeof( partVPMats ), 16 ), true );
		shadowPCB.Init( Util::AlignSize( sizeof( partFarClips ), 16 ), false, partFarClips );
	}

	/*for( SkinModelRender*& s : g_testSk ){
		s = new SkinModelRender();
		s->Init( L"Assets/modelData/Troll.cmo" );
	}*/
}

void CascadeShadow::RemoveShadowCaster( SkinModelRender * render ){
	for( auto shadowItr = m_shadowCasters.begin(); shadowItr != m_shadowCasters.end(); shadowItr++ ){
		if( render == *shadowItr ){
			m_shadowCasters.erase( shadowItr );
			return;
		}
	}
}

void CascadeShadow::RenderToShadowMap( ID3D11DeviceContext * dc ){

	//各垂台でドロー
	int pCount = 0;
	for( auto& p : parts ){

		//ドロー
		p.SetLightDir( m_dir );
		p.RenderToShadowMap( dc, m_shadowCasters );

		//SRVをセット
		partSRVs[pCount] = p.GetShadowMapSRV();

		//VP行列を更新
		partVPMats[pCount++] = p.GetVPMat();
	}
	shadowVCB.UpdateData( partVPMats );
	shadowVCB.SetToContext( ShaderType::VS, enSkinModelCBReg_Shadow );
	shadowPCB.SetToContext( ShaderType::PS, enSkinModelCBReg_ShadowFar );
}