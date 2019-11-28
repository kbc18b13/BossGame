#include "stdafx.h"
#include "RenderObjectManager.h"

RenderObjectManager g_ROManager;

RenderObjectManager::RenderObjectManager(){}


RenderObjectManager::~RenderObjectManager(){}

void RenderObjectManager::Init(){
    m_shadowMap.Init( 2048, 2048 );
    m_postEffect.Init();

    //ポストエフェクト前に書き込むレンダリングターゲット
    m_defaultTarget.Init( FRAME_BUFFER_W, FRAME_BUFFER_H, DXGI_FORMAT_R8G8B8A8_UNORM );

    //モノクロシェーダー
    m_monoShader.Load( "Assets/shader/monochrome.fx", "PSMain", Shader::EnType::PS );
}

void RenderObjectManager::Render(){
    ID3D11DeviceContext* dc = g_graphicsEngine->GetD3DDeviceContext();

    //シャドウマップの描画。
    m_shadowMap.RenderToShadowMap( dc );

    //描画先を通常ターゲットへ。
    m_defaultTarget.SetToContext( dc );
    m_defaultTarget.Clear(CVector4(0, 0, 0, 1));

    //通常描画オブジェクトの描画
    m_defaultRender.Render();

    //物理ワイヤーフレーム
    g_physics.DebugDraw();

    //描画先をフレームバッファへ。
    g_graphicsEngine->BegineFrameBuffer();

    //ポストエフェクト適用。
    m_postEffect.DrawScreenRect((ID3D11PixelShader*)m_monoShader.GetBody(), m_defaultTarget.GetRenderTargetSRV());

    //HUD描画オブジェクトの描画。
    m_HUDRender.Render();
}
