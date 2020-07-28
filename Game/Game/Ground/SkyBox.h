#pragma once
#include "graphics/IRenderObject.h"

class SkyBox : IRenderObject{
public:
	void Init(const wchar_t* modelPath);

	void Render() override;

	void SetStencilRef( int ref ){
		m_model.SetStencilRef( ref );
	}

	void SetRot(const CQuaternion& rot );

private:
	SkinModel m_model;
	ComPtr<ID3D11DepthStencilState> m_depthState;
};

