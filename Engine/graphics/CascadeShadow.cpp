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
		parts[0].Init( w, h );
		parts[0].SetPart( 0, 0.07f );

		parts[1].Init( w, h, 0.5f );
		parts[1].SetPart( parts[0].GetFar(), 0.15f );

		parts[2].Init( w, h, 0.4f );
		parts[2].SetPart( parts[1].GetFar(), 0.3f );

		parts[3].Init( w, h, 0.3f );
		parts[3].SetPart( parts[2].GetFar(), 0.5f );

		parts[4].Init( w, h, 0.2f );
		parts[4].SetPart( parts[3].GetFar(), 0.7f );

		for( int i = 0; i < ARRAYSIZE( parts ); i++ ){
			partFarClips[i] = parts[i].GetCameraFar();
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
		sampDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
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

	//ラスタライザステート設定
	{
		D3D11_RASTERIZER_DESC rDesc{};
		rDesc.CullMode = D3D11_CULL_BACK;
		rDesc.FillMode = D3D11_FILL_SOLID;
		rDesc.DepthBias = 1000;
		rDesc.SlopeScaledDepthBias = 0.8f;
		rDesc.DepthBiasClamp = 1000000;

		HRESULT res = g_graphicsEngine->GetD3DDevice()->CreateRasterizerState( &rDesc, &m_rasterState );
		if( FAILED( res ) ){
			abort();
		}
	}
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

	//ラスタライザステートを変更
	ComPtr<ID3D11RasterizerState> oldRS;
/*	dc->RSGetState( &oldRS );
	dc->RSSetState( m_rasterState.Get() );
	*/
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

	//影用定数バッファを設定。RenderObjectManagerの次ステップで使われる。
	shadowVCB.UpdateData( partVPMats );
	shadowVCB.SetToContext( ShaderType::VS, enSkinModelCBReg_Shadow );
	shadowPCB.SetToContext( ShaderType::PS, enSkinModelCBReg_ShadowFar );

	//ラスタライザステートを戻す。
//x	dc->RSSetState( oldRS.Get() );
}