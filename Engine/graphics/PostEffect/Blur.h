#pragma once
#include "..\RenderTarget.h"
#include "PostEffect.h"

class Blur{
public:
    Blur();
    ~Blur();

    void Init( UINT sourceWidth, UINT sourceHeight, DXGI_FORMAT format);
    void ApplyEffect(ID3D11ShaderResourceView* srv, PostEffect& postEffect);

    ID3D11ShaderResourceView* GetSRV(){
        return m_lastBlurTarget.GetRenderTargetSRV();
    }

private:
    RenderTarget m_widthBlurTarget;
    RenderTarget m_lastBlurTarget;

    Shader m_vShaderX;
    Shader m_vShaderY;
    Shader m_pShader;

    ID3D11Buffer* m_weightCB;
};

