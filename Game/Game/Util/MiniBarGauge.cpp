#include "stdafx.h"
#include "MiniBarGauge.h"
#include "graphics/RenderObjectManager.h"

MiniBarGauge::MiniBarGauge(){}

MiniBarGauge::~MiniBarGauge(){}

void MiniBarGauge::Init( const wchar_t * outImagePath, const wchar_t * inImagePath, UINT width, UINT height ){
	m_out.Init( outImagePath, width, height );
	m_in.Init( inImagePath, width, height );
	g_ROManager.AddDefaultRender( this );
}

void MiniBarGauge::view(){
	if( time < 0 && time <= 2.9f ){
		time = 2.9f;
	} else{
		time = c_time;
	}
}

void MiniBarGauge::Render(){
	if( m_active ){

		g_graphicsEngine->ResetBlendState();

		if( time <= 0 ){
			return;
		}
		float alpha;
		if( time > 2.9f ){
			alpha = ( 3.0f - time ) * 10;
		} else{
			alpha = std::min(time, 1.0f);
		}
		time -= GameTime::GetDeltaTime();
		m_out.SetMulColor( CVector4( 1, 1, 1, alpha ) );
		m_in.SetMulColor( CVector4( 1, 0, 0, alpha ) );

		CVector4 pos = CVector4(m_pos.x, m_pos.y, m_pos.z, 1);

		g_camera3D.GetViewMatrix().Mul( pos );

		/*float halfAngle = g_camera3D.GetViewAngle() / 2;
		float scale = tanf( halfAngle ) * 2;*/
		float scale = 500 / ( pos.z);

		g_camera3D.GetProjectionMatrix().Mul( pos );

		pos /= pos.w;

		CVector2 pos2D( pos.x * FRAME_BUFFER_W * 0.5f, pos.y * FRAME_BUFFER_H * 0.5f );
		pos2D.x += m_out.GetWidth() * scale / 2;

		m_out.UpdateWorldMatrix( pos2D, CVector2(scale, scale), CQuaternion::Identity(),
								 CVector2( 0.5f, 0.f ) , pos.z+0.0001f);
		m_in.UpdateWorldMatrix( pos2D, CVector2( m_percent*scale, scale ), CQuaternion::Identity(),
								CVector2( 0.5f, 0.f ) , pos.z);
		m_out.Draw();
		m_in.Draw();
	}
}
