#include "stdafx.h"
#include "system/system.h"
#include "Actor/Player/Player.h"
#include "level/Level.h"
#include "graphics/SpriteRender.h"
///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//�J�������������B
	g_camera3D.SetPosition({ 0.0f, 50.0f,-50.0f });
	g_camera3D.SetTarget({ 0.0f, 0.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);

	GOManager().Init(10, 5);

	GOManager().NewGO<Player>(0);

	SpriteRender* sp = GOManager().NewGO<SpriteRender>(0);
	sp->Init(L"Assets/sprite/BLADERNL.dds", 600, 600);

	CVector2 pos(0,0);
	CQuaternion rot = CQuaternion::Identity();;

	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//�����G���W���̍X�V�B
		g_physics.Update();
		//�J�����̍X�V�B
		g_camera3D.Update();

		//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̍X�V�B
		GOManager().Update();

		pos.x += g_pad->GetLStickXF()*50;
		pos.y += g_pad->GetLStickYF()*50;

		CQuaternion r;
		r.SetRotationDeg(CVector3::AxisZ(), g_pad->GetRStickXF()*2);
		rot.Multiply(r);
		sp->SetPos(pos);
		sp->SetRot(rot);

		//�`��I���B
		g_graphicsEngine->EndRender();
	}
}