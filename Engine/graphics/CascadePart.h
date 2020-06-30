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
	/// 描画される範囲を0～1とした場合の近面と遠面を設定する
	/// </summary>
	void SetPart( float nearClip, float farClip ){
		m_near = nearClip;
		m_far = farClip;
	}

	float GetNear(){
		return m_near;
	}

	/// <summary>
	/// カメラの近、遠平面を考慮した近平面を返す。
	/// </summary>
	float GetCameraNear(){
		return g_camera3D.GetNear() + ( m_near * ( g_camera3D.GetFar() - g_camera3D.GetNear() ) );
	}

	float GetFar(){
		return m_far;
	}

	/// <summary>
	/// カメラの近、遠平面を考慮した遠平面を返す。
	/// </summary>
	float GetCameraFar(){
		return g_camera3D.GetNear() + ( m_far * ( g_camera3D.GetFar() - g_camera3D.GetNear() ) );
	}

	void SetLightDir( const CVector3& dir ){
		m_dir = dir;
	}

	/// <summary>
	/// シャドウマップに描画。
	/// </summary>
	void RenderToShadowMap( ID3D11DeviceContext* dc, std::vector<SkinModelRender*>& casters );

	/// <summary>
	/// シャドウマップのSRVを取得。
	/// </summary>
	/// <returns>シャドウマップのSRV</returns>
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

