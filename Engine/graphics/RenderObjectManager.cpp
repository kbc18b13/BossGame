#include "stdafx.h"
#include "RenderObjectManager.h"

RenderObjectManager g_ROManager;

RenderObjectManager::RenderObjectManager(){}


RenderObjectManager::~RenderObjectManager(){}

void RenderObjectManager::Init(){
    m_shadowMap.Init( 2048, 2048 );
    m_postEffect.Init();

    //ポストエフェクト前に書き込むレンダリングターゲット
    m_defaultTarget.Init( FRAME_BUFFER_W, FRAME_BUFFER_H, DXGI_FORMAT_R16G16B16A16_FLOAT);

    //モノクロシェーダー
    m_monoShader.Load( "Assets/shader/PostEffect.fx", "PSDefault", Shader::EnType::PS );

	m_bloom.Init();
    //m_blur.Init( FRAME_BUFFER_W, FRAME_BUFFER_H, FRAME_BUFFER_FORMAT );
}

void RenderObjectManager::Render(){
    ID3D11DeviceContext* dc = g_graphicsEngine->GetD3DDeviceContext();

    //シャドウマップの描画。
    m_shadowMap.RenderToShadowMap( dc );

    //描画先を通常ターゲットへ。
    m_defaultTarget.SetToContext( dc );
    m_defaultTarget.Clear(CVector4(0, 54.f/255, 106.f/255, 1));

    //通常描画オブジェクトの描画
    m_defaultRender.Render();

    //物理ワイヤーフレーム
    g_physics.DebugDraw();

	/*m_blur.SetSource( m_defaultTarget.GetRenderTargetSRV() );
    m_blur.ApplyEffect( m_postEffect );*/

	//ブルーム
	m_bloom.SetSource( m_defaultTarget.GetRenderTargetSRV() );
	m_bloom.SetTarget( &m_defaultTarget );
	m_bloom.ApplyEffect( m_postEffect );

	//描画先をフレームバッファへ。
	g_graphicsEngine->BegineFrameBuffer();

    //ポストエフェクト適用。
    m_postEffect.DrawScreenRect(m_defaultTarget.GetRenderTargetSRV() , (ID3D11PixelShader*)m_monoShader.GetBody());

    //HUD描画オブジェクトの描画。
    m_HUDRender.Render();
}
