#pragma once
#include "RenderTarget.h"
#include "CascadePart.h"
#include "graphics/Parts/ConstantBuffer.h"

class SkinModelRender;

class CascadeShadow{
public:
	CascadeShadow();
	~CascadeShadow();

	void Init( unsigned int w, unsigned int h );

	void AddShadowCaster( SkinModelRender* render ){
		m_shadowCasters.push_back( render );
	}
	void RemoveShadowCaster( SkinModelRender* render );


	/// <summary>
	/// シャドウマップに描画。
	/// </summary>
	void RenderToShadowMap( ID3D11DeviceContext* dc );

	/// <summary>
	/// シャドウマップのSRVを取得。
	/// </summary>
	ID3D11ShaderResourceView** GetSRVPointer(){
		return partSRVs;
	}

	/// <summary>
	/// シャドウマップのSRV個数を取得
	/// </summary>
	int GetSRVNum()const{
		return partNum;
	}

private:
	void UpdateMatirx(CVector3( &verts )[8] );

	CVector3 m_lightCameraPosition = CVector3::Zero();	//ライトカメラの視点。
	CVector3 m_lightCameraTarget = CVector3::Zero();	//ライトカメラの注視点。
	CMatrix m_lightViewMatrix = CMatrix::Identity();	//ライトビュー行列。
	CMatrix m_lightProjMatrix = CMatrix::Identity();	//ライトプロジェクション行列。
	
	ComPtr<ID3D11SamplerState> m_sampler;//サンプラステート

	//分割の数
	static constexpr int partNum = 5;

	//分割ごとのSRV
	ID3D11ShaderResourceView* partSRVs[partNum];

	//分割描画オブジェクト
	CascadePart parts[partNum];

	//分割ごとのVP行列
	CMatrix partVPMats[partNum];
	ConstantBuffer shadowVCB;

	//分割ごとのファークリップ
	float partFarClips[partNum];
	ConstantBuffer shadowPCB;


	std::vector<SkinModelRender*> m_shadowCasters;

	CVector3 m_dir{ -1, -1, -1 };
};

