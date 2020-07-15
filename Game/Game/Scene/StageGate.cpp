#include "stdafx.h"
#include "StageGate.h"

StageGate::StageGate(){}

StageGate::~StageGate(){}

void StageGate::Init( IStage * now, IStage * next, const CVector3 & pos ){
	SetNowStage( now );
	SetNextStage( next );
	m_pos = pos;

	m_col.Init( this->Update, CVector3( 480, 355, 250 ), pos );

	{
		SkinModelRenderInitParam param;
		param.filePath = L"Assets/modelData/StageGatge.cmo";
		param.isStencliDraw = true;
		m_gateModel.Init( param );

		D3D11_RASTERIZER_DESC rsDesc{};
		rsDesc.CullMode = D3D11_CULL_NONE;
		rsDesc.FillMode = D3D11_FILL_SOLID;
		rsDesc.DepthClipEnable = true;
		ID3D11RasterizerState* rsState;
		g_graphicsEngine->GetD3DDevice()->CreateRasterizerState( &rsDesc, &rsState );
		m_gateModel.GetModel().SetRasterState( rsState );

		m_gateModel.Update();
	}

	m_gateModel.GetModel().FindMesh( []( const std::unique_ptr<DirectX::ModelMeshPart>& mesh ){
		mesh
	} );
}

void StageGate::Update(){

}
