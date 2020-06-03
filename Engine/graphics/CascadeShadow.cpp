#include "stdafx.h"
#include "CascadeShadow.h"
#include "SkinModelRender.h"

SkinModelRender* g_testSk[4] = {};

CascadeShadow::CascadeShadow(){}


CascadeShadow::~CascadeShadow(){}

void CascadeShadow::Init( unsigned int w, unsigned int h ){
    m_renderTarget.Init( w, h, DXGI_FORMAT_R32_FLOAT );
    m_vpMatCB.Init( sizeof( CMatrix ), false );

	for( SkinModelRender*& s : g_testSk ){
		s = new SkinModelRender();
		s->Init( L"Assets/modelData/Troll.cmo" );
	}
}

void CascadeShadow::RemoveShadowCaster( SkinModelRender * render ){
    for( auto shadowItr = m_shadowCasters.begin(); shadowItr != m_shadowCasters.end(); shadowItr++ ){
        if( render == *shadowItr ){
            m_shadowCasters.erase( shadowItr );
            return;
        }
    }
}

void CascadeShadow::RenderToShadowMap( ID3D11DeviceContext * dc ){
    //レンダーターゲットとビューポートを更新
    auto rt = m_renderTarget.GetRenderTargetView();
    dc->OMSetRenderTargets( 1, &rt, m_renderTarget.GetDepthStensilView() );
    dc->RSSetViewports( 1, m_renderTarget.GetViewport() );

    //シャドウマップをクリア。
    //一番奥のZは1.0なので、1.0で塗りつぶす。
    m_renderTarget.Clear( CVector4( 1.0f, 1.0f, 1.0f, 1.0f ) );

	CVector3 nearPos = g_camera3D.GetPosition() + g_camera3D.GetFront() * g_camera3D.GetNear();
	CVector3 farPos = g_camera3D.GetPosition() + g_camera3D.GetFront() * g_camera3D.GetFar();
	const float viewAngleTan = tanf(g_camera3D.GetViewAngle()/2);

	CVector3 verts[8];
	const CVector3 nearY = g_camera3D.GetUp() * viewAngleTan * g_camera3D.GetNear();
	const CVector3 nearX = g_camera3D.GetRight() * viewAngleTan * g_camera3D.GetNear() * g_camera3D.GetAspect();
	verts[0] = nearPos + nearY + nearX;
	verts[1] = nearPos - nearY + nearX;
	verts[2] = nearPos + nearY - nearX;
	verts[3] = nearPos - nearY - nearX;

	const CVector3 farY = g_camera3D.GetUp() * viewAngleTan * g_camera3D.GetFar();
	const CVector3 farX = g_camera3D.GetRight() * viewAngleTan * g_camera3D.GetFar() * g_camera3D.GetAspect();
	verts[4] = farPos + farY + farX;
	verts[5] = farPos - farY + farX;
	verts[6] = farPos + farY - farX;
	verts[7] = farPos - farY - farX;

	

	UpdateMatirx( verts );

    //シャドウキャスターをシャドウマップにレンダリング。
    for( auto& caster : m_shadowCasters ){
        caster->Render( EnRenderMode::ShadowMap, m_lightViewMatrix, m_lightProjMatrix );
    }

    CMatrix mat;
    mat.Mul( m_lightViewMatrix, m_lightProjMatrix );
    m_vpMatCB.UpdateData( &mat );
    m_vpMatCB.SetToContext( ShaderType::VS, 6 );
}

void CascadeShadow::UpdateMatirx(CVector3( &verts )[8] ){
	m_lightViewMatrix = DirectX::XMMatrixLookToLH( CVector3::Zero(), m_dir, CVector3::Up() );
	for( CVector3& v : verts ){
		m_lightViewMatrix.Mul( v );
	}

	//g_physics.DrawLine( look - ( m_dir * 2000 ), look + ( m_dir * 3000 ), { 1,0,0 } );

	//AABBを作成
	constexpr float max_float = std::numeric_limits<float>().max();
	constexpr float min_float = std::numeric_limits<float>().min();
	CVector3 minPos{ max_float ,max_float ,max_float };
	CVector3 maxPos{ min_float ,min_float ,min_float };
	for( CVector3& v : verts ){
		minPos.Min( v );
		maxPos.Max( v );
	}

	CVector3 center = ( minPos + maxPos ) / 2;
	constexpr float nearClip = 1.0f;
	float moveBack = ( center.z - minPos.z ) + nearClip;

	CVector3 tPos = center;
	for( int i = 0; i < 4; i++ ){
		g_testSk[i]->SetPos( tPos );
		g_testSk[i]->Update();
	}

	//AABBにしたがってビュー行列を再設定
	m_lightViewMatrix = DirectX::XMMatrixLookToLH( center - ( m_dir * moveBack ), m_dir, CVector3::Up() );
	m_lightProjMatrix = DirectX::XMMatrixOrthographicLH( maxPos.x - minPos.x, maxPos.y - minPos.y,
														 nearClip, maxPos.z - minPos.z + nearClip );
}
