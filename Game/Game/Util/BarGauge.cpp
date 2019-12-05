#include "stdafx.h"
#include "BarGauge.h"
#include "graphics/RenderObjectManager.h"

BarGauge::BarGauge(){}


BarGauge::~BarGauge(){}

void BarGauge::Init( const wchar_t* outImagePath, const wchar_t* inImagePath, UINT width, UINT height ){
	m_out.Init( outImagePath, width, height );
	m_in.Init( inImagePath, width, height );
	g_ROManager.AddHUDRender( this );
}

void BarGauge::Render(){
	m_out.UpdateWorldMatrix( m_pos, CVector2::One(), CQuaternion::Identity(), CVector2( 0.5f, 0.f ) );
	m_in.UpdateWorldMatrix( m_pos, CVector2( m_percent, 1 ), CQuaternion::Identity(), CVector2( 0.5f, 0.f ) );
	m_out.Draw();
	m_in.Draw();
}
