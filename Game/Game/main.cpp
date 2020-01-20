#include "stdafx.h"
#include "system/system.h"
#include "Actor/Player/Player.h"
#include "level/Level.h"
#include "Scene/Title.h"
#include "graphics/RenderObjectManager.h"
#include "graphics/FontRender.h"
///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////

//void timestamp(const wchar_t* t){
//	static wchar_t fpsText[50];
//	static clock_t before = 0;
//	clock_t now = clock();
//	swprintf( fpsText, L" : %ld\n", now - before );
//	OutputDebugStringW( t );
//	OutputDebugStringW( fpsText );
//	before = now;
//}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	
	//�f�o�b�O�L����
	g_physics.setDebugDraw(true);

	g_camera3D.Init();
	g_camera3D.SetTarget({ 0.0f, 20.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);

    //�����_�[�I�u�W�F�N�g�}�l�[�W���[�̏�����
    g_ROManager.Init();

    //�Q�[���I�u�W�F�N�g�}�l�[�W���[�̏�����
	GOManager().Init(10, 5);

#ifdef DEBUG
	FontRender fpsRender;
	fpsRender.SetPos(CVector2(500,500) );
	wchar_t fpsText[20];
	fpsRender.SetText( fpsText );
#endif

	NewGO<Title>(0);
	
	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		GameTime::UpdateTime();

		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}

		//�����G���W���̍X�V�B
		g_physics.Update();

		//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̍X�V�B
		GOManager().Update();

#ifdef _DEBUG
		swprintf( fpsText, L"FPS:%5f\n", GameTime::GetFPS());
#endif
		
        //�`��J�n�B
        g_graphicsEngine->BegineRender();

		//�`��I�u�W�F�N�g�̕`��B
        g_ROManager.Render();

		//�`��I���B
		g_graphicsEngine->EndRender();

	}
}