#include "stdafx.h"
#include "system/system.h"
#include "Actor/Player/Player.h"
#include "level/Level.h"
#include "Scene/Title.h"
#include "graphics/RenderObjectManager.h"
#include "graphics/FontRender.h"
#include "Util/Fade.h"

EffekseerRenderer::Renderer* g_effectRender = nullptr;
Effekseer::Manager* g_effectManager = nullptr;

void InitEffekseer();
void UpdateEffekseer();

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow ){
	//ゲームの初期化。
	InitGame( hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game" );

	g_camera3D.Init();
	g_camera3D.SetTarget( { 0.0f, 20.0f, 0.0f } );
	g_camera3D.SetFar( 10000.0f );

	//サウンドマネージャーの初期化
	g_soundEngine.Init();

	//レンダーオブジェクトマネージャーの初期化
	g_ROManager.Init();

	//ゲームオブジェクトマネージャーの初期化
	GOManager().Init( 10, 5 );

	//エフェクシア初期化
	InitEffekseer();

#ifdef _DEBUG
	FontRender fpsRender;
	fpsRender.SetPos( CVector2( 500, 500 ) );
	wchar_t fpsText[20];
	fpsRender.SetText( fpsText );
#endif

	bool debug = false;
	NewGO<Title>( 0 );

	Fade::Out();

	//ゲームループ。
	while( DispatchWindowMessage() == true ){
		GameTime::UpdateTime();

		//ゲームパッドの更新。	
		for( auto& pad : g_pad ){
			pad.Update();
		}

		if( g_pad->IsTrigger( enButtonY ) ){
			debug = !debug;
			g_physics.setDebugDraw( debug );
		}

		//物理エンジンの更新。
		g_physics.Update();

		//ゲームオブジェクトマネージャーの更新。
		GOManager().Update();

#ifdef _DEBUG
		swprintf( fpsText, L"FPS:%5f\n", GameTime::GetFPS() );
#endif

		//描画開始。
		g_graphicsEngine->BegineRender();

		//描画オブジェクトの描画。
		g_ROManager.Render();

		//描画終了。
		g_graphicsEngine->EndRender();

		//サウンドエンジンの更新。
		g_soundEngine.Update();
	}
}


void InitEffekseer(){
	//エフェクトマネージャーの初期化
	g_effectRender = EffekseerRendererDX11::Renderer::Create( g_graphicsEngine->GetD3DDevice(),
															  g_graphicsEngine->GetD3DDeviceContext(),
															  255 );
	g_effectManager = Effekseer::Manager::Create( 255 );

	// 描画用インスタンスから描画機能を設定
	g_effectManager->SetSpriteRenderer( g_effectRender->CreateSpriteRenderer() );
	g_effectManager->SetRibbonRenderer( g_effectRender->CreateRibbonRenderer() );
	g_effectManager->SetRingRenderer( g_effectRender->CreateRingRenderer() );
	g_effectManager->SetTrackRenderer( g_effectRender->CreateTrackRenderer() );
	g_effectManager->SetModelRenderer( g_effectRender->CreateModelRenderer() );

	// 描画用インスタンスからテクスチャの読込機能を設定
	// 独自拡張可能、現在はファイルから読み込んでいる。
	g_effectManager->SetTextureLoader( g_effectRender->CreateTextureLoader() );
	g_effectManager->SetModelLoader( g_effectRender->CreateModelLoader() );
}

void UpdateEffekseer(){
	//Effekseerカメラ行列を設定。
	//まずはEffeseerの行列型の変数に、カメラ行列とプロジェクション行列をコピー。
	Effekseer::Matrix44 efCameraMat;
	g_camera3D.GetViewMatrix().CopyTo( efCameraMat.Values[0] );
	Effekseer::Matrix44 efProjMat;
	g_camera3D.GetProjectionMatrix().CopyTo( efProjMat.Values[0] );
	//カメラ行列とプロジェクション行列を設定。
	g_effectRender->SetCameraMatrix( efCameraMat );
	g_effectRender->SetProjectionMatrix( efProjMat );
	//Effekseerを更新。
	g_effectManager->Update();
}