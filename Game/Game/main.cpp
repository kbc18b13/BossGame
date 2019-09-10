#include "stdafx.h"
#include "system/system.h"
#include "Actor/Player/Player.h"
#include "level/Level.h"
#include "graphics/SpriteRender.h"
///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//カメラを初期化。
	g_camera3D.SetPosition({ 0.0f, 50.0f,-50.0f });
	g_camera3D.SetTarget({ 0.0f, 0.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);

	GOManager().Init(10, 5);

	GOManager().NewGO<Player>(0);

	SpriteRender* sp = GOManager().NewGO<SpriteRender>(0);
	sp->Init(L"Assets/sprite/BLADERNL.dds", 600, 600);

	CVector2 pos(0,0);
	CQuaternion rot = CQuaternion::Identity();;

	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//描画開始。
		g_graphicsEngine->BegineRender();
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//物理エンジンの更新。
		g_physics.Update();
		//カメラの更新。
		g_camera3D.Update();

		//ゲームオブジェクトマネージャーの更新。
		GOManager().Update();

		pos.x += g_pad->GetLStickXF()*50;
		pos.y += g_pad->GetLStickYF()*50;

		CQuaternion r;
		r.SetRotationDeg(CVector3::AxisZ(), g_pad->GetRStickXF()*2);
		rot.Multiply(r);
		sp->SetPos(pos);
		sp->SetRot(rot);

		//描画終了。
		g_graphicsEngine->EndRender();
	}
}