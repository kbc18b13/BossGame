#pragma once

#include "RenderTarget.h"
#include "graphics/Parts/ConstantBuffer.h"

class CascadePart{
public:
	void SetPart(float nearClip, float farClip){
		m_near = nearClip;
		m_far = farClip;
	}

	void SetLightDir( const CVector3& dir ){
		m_dir = dir;
	}

	/// <summary>
	/// �V���h�E�}�b�v�ɕ`��B
	/// </summary>
	void RenderToShadowMap( ID3D11DeviceContext* dc , std::vector<SkinModelRender*>& casters);

	/// <summary>
	/// �V���h�E�}�b�v��SRV���擾�B
	/// </summary>
	/// <returns>�V���h�E�}�b�v��SRV</returns>
	ID3D11ShaderResourceView* GetShadowMapSRV(){
		return m_renderTarget.GetRenderTargetSRV();
	}

private:

	CVector3 m_dir;

	float m_near;
	float m_far;

	RenderTarget m_renderTarget;

	ConstantBuffer m_vpMatCB;

	CMatrix m_lightViewMatrix = CMatrix::Identity();	//���C�g�r���[�s��B
	CMatrix m_lightProjMatrix = CMatrix::Identity();	//���C�g�v���W�F�N�V�����s��B
};

