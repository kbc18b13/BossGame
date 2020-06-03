#include "stdafx.h"
#include "CascadePart.h"
#include <numeric>

void CascadePart::RenderToShadowMap( ID3D11DeviceContext * dc, std::vector<SkinModelRender*>& casters ){
	CVector3 cameraNear = g_camera3D.GetPosition() + g_camera3D.GetFront() * g_camera3D.GetNear();
	CVector3 cameraVec = g_camera3D.GetFront() * ( g_camera3D.GetNear() - g_camera3D.GetFar() );

	CVector3 nearPos = nearPos + cameraVec * m_near;
	CVector3 farPos = nearPos + cameraVec * m_far;

	float viewAngleTan = tanf( g_camera3D.GetViewAngle() / 2 );

	//視錐台の8頂点を取得
	CVector3 verts[8];
	verts[0] = nearPos + cameraVec * m_near + ( g_camera3D.GetUp() * viewAngleTan );
	verts[1] = nearPos + ( g_camera3D.GetUp() * -viewAngleTan );
	verts[2] = nearPos + ( g_camera3D.GetRight() * viewAngleTan * g_camera3D.GetAspect() );
	verts[3] = nearPos + ( g_camera3D.GetRight() * -viewAngleTan * g_camera3D.GetAspect() );
	verts[4] = farPos + ( g_camera3D.GetUp() * viewAngleTan );
	verts[5] = farPos + ( g_camera3D.GetUp() * -viewAngleTan );
	verts[6] = farPos + ( g_camera3D.GetRight() * viewAngleTan * g_camera3D.GetAspect() );
	verts[7] = farPos + ( g_camera3D.GetRight() * -viewAngleTan * g_camera3D.GetAspect() );

	m_lightViewMatrix = DirectX::XMMatrixLookToLH( CVector3::Zero(), m_dir, CVector3::Up() );

	//ライトのビュー行列で変換
	for( CVector3& v : verts ){
		m_lightViewMatrix.Mul( v );
	}

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

	//AABBにしたがってビュー行列を再設定
	m_lightViewMatrix = DirectX::XMMatrixLookToLH( center - ( m_dir * moveBack ), m_dir, CVector3::Up() );
	m_lightProjMatrix = DirectX::XMMatrixOrthographicLH( maxPos.x - minPos.x, maxPos.y - minPos.y,
														 nearClip, maxPos.z - minPos.z + nearClip );

	//レンダーターゲットとビューポートを更新
	auto rt = m_renderTarget.GetRenderTargetView();
	dc->OMSetRenderTargets( 1, &rt, m_renderTarget.GetDepthStensilView() );
	dc->RSSetViewports( 1, m_renderTarget.GetViewport() );

	//シャドウマップをクリア。
	//一番奥のZは1.0なので、1.0で塗りつぶす。
	m_renderTarget.Clear( CVector4( 1.0f, 1.0f, 1.0f, 1.0f ) );

	//描画
	for( SkinModelRender* r : casters ){
		r->Render( EnRenderMode::ShadowMap, m_lightViewMatrix, m_lightProjMatrix );
	}
}
