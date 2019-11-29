#include "stdafx.h"
#include "Blur.h"


Blur::Blur(){}


Blur::~Blur(){
    m_weightCB->Release();
}

void Blur::Init( UINT sourceWidth, UINT sourceHeight, DXGI_FORMAT format ){
    //レンダーターゲットを初期化
    m_widthBlurTarget.Init( sourceWidth/2, sourceHeight, format );
    m_lastBlurTarget.Init( sourceWidth/2, sourceHeight/2, format );

    //シェーダーを初期化
    m_vShaderX.Load( "Assets/shader/Blur.fx", "VSBlurX", Shader::EnType::VS );
    m_vShaderY.Load( "Assets/shader/Blur.fx", "VSBlurY", Shader::EnType::VS );
    m_pShader.Load( "Assets/shader/Blur.fx", "PSBlur", Shader::EnType::PS );


}

void Blur::ApplyEffect( ID3D11ShaderResourceView* srv, PostEffect& postEffect ){
    ID3D11DeviceContext* dc = g_graphicsEngine->GetD3DDeviceContext();

    using VS = ID3D11VertexShader;
    using PS = ID3D11PixelShader;


    m_widthBlurTarget.SetToContext( dc );
    postEffect.DrawScreenRect( srv, (PS*)m_pShader.GetBody(), (VS*)m_vShaderX.GetBody() );

    m_lastBlurTarget.SetToContext( dc );
    postEffect.DrawScreenRect( m_widthBlurTarget.GetRenderTargetSRV()
                               ,(PS*)m_pShader.GetBody(), (VS*)m_vShaderY.GetBody() );

}
