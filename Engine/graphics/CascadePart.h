#pragma once

#include "RenderTarget.h"
#include "graphics/Parts/ConstantBuffer.h"

class CascadePart{
public:
	void Init( UINT w, UINT h, float scale ){
		Init( w*scale, h*scale );
	}
	void Init( UINT w, UINT h );

	/// <summary>
	/// �`�悳���͈͂�0�`1�Ƃ����ꍇ�̋ߖʂƉ��ʂ�ݒ肷��
	/// </summary>
	void SetPart( float nearClip, float farClip ){
		m_near = nearClip;
		m_far = farClip;
	}

	float GetNear(){
		return m_near;
	}

	/// <summary>
	/// �J�����̋߁A�����ʂ��l�������ߕ��ʂ�Ԃ��B
	/// </summary>
	float GetCameraNear(){
		return g_camera3D.GetNear() + ( m_near * ( g_camera3D.GetFar() - g_camera3D.GetNear() ) );
	}

	float GetFar(){
		return m_far;
	}

	/// <summary>
	/// �J�����̋߁A�����ʂ��l�����������ʂ�Ԃ��B
	/// </summary>
	float GetCameraFar(){
		return g_camera3D.GetNear() + ( m_far * ( g_camera3D.GetFar() - g_camera3D.GetNear() ) );
	}

	void SetLightDir( const CVector3& dir ){
		m_dir = dir;
	}

	/// <summary>
	/// �V���h�E�}�b�v�ɕ`��B
	/// </summary>
	void RenderToShadowMap( ID3D11DeviceContext* dc, std::vector<SkinModelRender*>& casters );

	/// <summary>
	/// �V���h�E�}�b�v��SRV���擾�B
	/// </summary>
	/// <returns>�V���h�E�}�b�v��SRV</returns>
	ID3D11ShaderResourceView* GetShadowMapSRV(){
		return m_renderTarget.GetRenderTargetSRV();
	}

	CMatrix GetVPMat() const{
		return m_vpMat;
	}

private:
	RenderTarget m_renderTarget;

	CVector3 m_dir;

	float m_near;
	float m_far;

	CMatrix m_vpMat;
};

