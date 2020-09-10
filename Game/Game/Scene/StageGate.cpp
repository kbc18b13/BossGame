#include "stdafx.h"
#include "StageGate.h"
#include "IStage.h"
#include "Actor/Player/Player.h"

StageGate::StageGate(){}

void StageGate::Destroy(){
	DeleteGO( m_AStage );
	DeleteGO( m_BStage );
}

void StageGate::Init( IStage * now, IStage * next,Player* p, const CVector3 & pos, const CQuaternion& rot ){
	SetAStage( now );
	SetBStage( next );
	m_pos = pos;

	m_player = p;

	m_toB = CVector3( 1, 0, 0 );
	rot.Multiply( m_toB );

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
	if( g_camera3D.GetPosition().DistanceSq( m_pos ) < pow2(700)){
		StencilUpdate();
	}

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

	float threshold = g_camera3D.GetNear();

	bool gateModelActive = true;

	//カメラ視点がゲートのどちら側にあるかを判定。
	if( dot < -threshold){
		ShowA();
	} else if( dot > threshold){
		ShowB();

	} else{
		//カメラがゲートと近い位置にある場合、カメラがゲートのどちら側を向いているかを判定。
		if( m_toB.Dot(g_camera3D.GetFront()) < 0 ){
			ShowA();
		} else{
			ShowB();
		}
		//カメラがゲートと近い位置にある場合、ステンシルへの書き込みは行わない。
		gateModelActive = false;
	}

	m_gateModel.SetActive( gateModelActive );
}

void StageGate::ShowA(){
	m_player->SetStage( m_AStage );
	m_AStage->SetStageStencilRef( 0 );
	m_BStage->SetStageStencilRef( 1 );
}

void StageGate::ShowB(){
	m_player->SetStage( m_BStage );
	m_AStage->SetStageStencilRef( 1 );
	m_BStage->SetStageStencilRef( 0 );
}
