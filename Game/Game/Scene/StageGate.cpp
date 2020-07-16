#include "stdafx.h"
#include "StageGate.h"
#include "IStage.h"

StageGate::StageGate(){}

StageGate::~StageGate(){}

void StageGate::Init( IStage * now, IStage * next, const CVector3 & pos, const CQuaternion& rot ){
	SetAStage( now );
	SetBStage( next );
	m_pos = pos;

	m_toB = CVector3( 1, 0, 0 );
	rot.Multiply( m_toB );

	m_col.Init( std::bind( &StageGate::StencilUpdate, this ), CVector3( 480, 355, 250 ), pos );

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
		m_gateModel.SetPos( m_pos );
		m_gateModel.SetRot( rot );
		m_gateModel.Update();
	}

	m_gateOutModel.Init({ L"Assets/modelData/GateOut.cmo"} );
	m_gateOutModel.SetPos( pos );
	m_gateOutModel.SetRot( rot );
	m_gateOutModel.Update();
}

void StageGate::Update(){
	m_col.Update();

	CQuaternion r = m_gateOutModel.GetRot();
	r.Multiply( CQuaternion::CreateRotDeg( m_toB, GameTime::GetDeltaTime() * 180 ) );
	m_gateOutModel.SetRot( r );
	m_gateModel.SetRot( r );
	m_gateModel.Update();
	m_gateOutModel.Update();
}

void StageGate::StencilUpdate(){
	CVector3 pos = g_camera3D.GetPosition();

	CVector3 gateToC = pos - m_pos;

	float dot = gateToC.Dot( m_toB );

	float thresholdCol = cosf(CMath::DegToRad( 10 ));

	if( dot < -thresholdCol ){
		m_AStage->SetStageStencilRef( 0 );
		m_BStage->SetStageStencilRef( 1 );

	} else if( dot > thresholdCol ){
		m_AStage->SetStageStencilRef( 1 );
		m_BStage->SetStageStencilRef( 0 );

	} else{
		m_AStage->SetStageStencilRef( 0 );
		m_BStage->SetStageStencilRef( 0 );
	}
}
