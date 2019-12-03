#pragma once
#include "..\RenderTarget.h"
#include "PostEffect.h"
#include "graphics/Parts/ConstantBuffer.h"

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

	static constexpr int blurRange = 8; //�u���[�̍L��
	struct CBData{
		float weights[blurRange];
		float width;
		float height;
	};
	ConstantBuffer m_weightCB;
};

