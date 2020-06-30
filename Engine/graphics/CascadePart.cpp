#include "stdafx.h"
#include "CascadePart.h"
#include <numeric>

extern SkinModelRender* g_testSk[4];

void CascadePart::Init( UINT w, UINT h ){
	m_renderTarget.Init( w, h, DXGI_FORMAT_R32_FLOAT );
}

void CascadePart::RenderToShadowMap( ID3D11DeviceContext * dc, std::vector<SkinModelRender*>& casters ){

	//視錐台の8頂点を取得(ワールド座標)
	CVector3 verts[8];
	{
		float l_near = GetCameraNear();
		float l_far = GetCameraFar();

		CVector3 nearPos = g_camera3D.GetPosition() + g_camera3D.GetFront() * l_near;
		CVector3 farPos = g_camera3D.GetPosition() + g_camera3D.GetFront() * l_far;

		float viewAngleTan = tanf( g_camera3D.GetViewAngle() / 2 );

		CVector3 nearUp = g_camera3D.GetUp() * ( viewAngleTan * l_near );
		CVector3 farUp = g_camera3D.GetUp() * ( viewAngleTan * l_far );

		CVector3 nearLateral = g_camera3D.GetRight() * ( viewAngleTan * l_near * g_camera3D.GetAspect() );
		CVector3 farLateral = g_camera3D.GetRight() * ( viewAngleTan * l_far * g_camera3D.GetAspect() );

		verts[0] = nearPos + nearUp + nearLateral;
		verts[1] = nearPos + nearUp - nearLateral;
		verts[2] = nearPos - nearUp + nearLateral;
		verts[3] = nearPos - nearUp - nearLateral;
		verts[4] = farPos  + farUp + farLateral;
		verts[5] = farPos  + farUp - farLateral;
		verts[6] = farPos  - farUp + farLateral;
		verts[7] = farPos  - farUp - farLateral;
	}

	//とりあえず位置を無視してライトビュー行列を作成
	CMatrix lightViewMatrix = DirectX::XMMatrixLookToLH( CVector4(0,0,0,1), m_dir, CVector3::Up() );

	//ライトのビュー行列で変換
	for( CVector3& v : verts ){
		lightViewMatrix.Mul( v );
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

	CVector3 centerPos = ( minPos + maxPos ) / 2; //AABBの中心
	CVector3 newPos = ( minPos + maxPos ) / 2; //AABBの中心
	float moveBack = ( newPos.z - minPos.z ) + g_camera3D.GetNear(); //中心から最も手前までの距離＋ニアクリップ
	newPos.z -= moveBack+1000; //新しいカメラ空間でのライトカメラ座標

	//AABBにしたがってビュー行列、プロジェクション行列を再設定
	lightViewMatrix.v[3] -= CVector4(newPos, 0);

	CMatrix lightProjMatrix =
		DirectX::XMMatrixOrthographicLH( maxPos.x - minPos.x, maxPos.y - minPos.y,
										g_camera3D.GetNear(), maxPos.z - minPos.z + g_camera3D.GetNear() + 1000 );


	//レンダーターゲットとビューポートを更新
	m_renderTarget.SetToContext( dc );

	//シャドウマップをクリア。一番奥のZは1.0なので、1.0で塗りつぶす。
	m_renderTarget.Clear( CVector4( 1.0f, 1.0f, 1.0f, 1.0f ) );

	//描画
	for( SkinModelRender* r : casters ){
		r->Render( EnRenderMode::ShadowMap, lightViewMatrix, lightProjMatrix );
	}

	//実際のモデル描画の際につかうビュープロジェクション行列を設定
	m_vpMat.Mul( lightViewMatrix, lightProjMatrix );
}
