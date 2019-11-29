#include "stdafx.h"
#include "system/system.h"
#include "Actor/Player/Player.h"
#include "level/Level.h"
#include "Scene/Title.h"
#include "graphics/RenderObjectManager.h"
///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//デバッグ有効化
	g_physics.setDebugDraw(true);

	g_camera3D.Init();
	g_camera3D.SetTarget({ 0.0f, 20.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);

    //レンダーオブジェクトマネージャーの初期化
    g_ROManager.Init();

    //ゲームオブジェクトマネージャーの初期化
	GOManager().Init(10, 5);

	NewGO<Title>(0);
	
	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		GameTime::UpdateTime();

		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}

		//物理エンジンの更新。
		g_physics.Update();

		//ゲームオブジェクトマネージャーの更新。
		GOManager().Update();
		
        //描画開始。
        g_graphicsEngine->BegineRender();

        //描画オブジェクトの描画。
        g_ROManager.Render();

		//描画終了。
		g_graphicsEngine->EndRender();
	}
}