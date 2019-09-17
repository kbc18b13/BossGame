#include "stdafx.h"
#include "system/system.h"
#include "Actor/Player/Player.h"
#include "level/Level.h"
#include "Scene/Title.h"
///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//�f�o�b�O�L����
	g_physics.setDebugDraw(true);

	g_camera3D.SetTarget({ 0.0f, 20.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);

	GOManager().Init(10, 5);

	NewGO<Title>(0);
	
	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		GameTime::UpdateTime();

		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		
		//�J�����̍X�V�B
		g_camera3D.Update();

		//�����G���W���̍X�V�B
		g_physics.Update();

		//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̍X�V�B
		GOManager().Update();

		//�`��I���B
		g_graphicsEngine->EndRender();
	}
}