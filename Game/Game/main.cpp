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
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow ){
	//�Q�[���̏������B
	InitGame( hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game" );

	g_camera3D.Init();
	g_camera3D.SetTarget( { 0.0f, 20.0f, 0.0f } );
	g_camera3D.SetFar( 10000.0f );

	//�T�E���h�}�l�[�W���[�̏�����
	g_soundEngine.Init();

	//�����_�[�I�u�W�F�N�g�}�l�[�W���[�̏�����
	g_ROManager.Init();

	//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̏�����
	GOManager().Init( 10, 5 );

	//�G�t�F�N�V�A������
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

	//�Q�[�����[�v�B
	while( DispatchWindowMessage() == true ){
		GameTime::UpdateTime();

		//�Q�[���p�b�h�̍X�V�B	
		for( auto& pad : g_pad ){
			pad.Update();
		}

		if( g_pad->IsTrigger( enButtonY ) ){
			debug = !debug;
			g_physics.setDebugDraw( debug );
		}

		//�����G���W���̍X�V�B
		g_physics.Update();

		//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̍X�V�B
		GOManager().Update();

#ifdef _DEBUG
		swprintf( fpsText, L"FPS:%5f\n", GameTime::GetFPS() );
#endif

		//�`��J�n�B
		g_graphicsEngine->BegineRender();

		//�`��I�u�W�F�N�g�̕`��B
		g_ROManager.Render();

		//�`��I���B
		g_graphicsEngine->EndRender();

		//�T�E���h�G���W���̍X�V�B
		g_soundEngine.Update();
	}
}


void InitEffekseer(){
	//�G�t�F�N�g�}�l�[�W���[�̏�����
	g_effectRender = EffekseerRendererDX11::Renderer::Create( g_graphicsEngine->GetD3DDevice(),
															  g_graphicsEngine->GetD3DDeviceContext(),
															  255 );
	g_effectManager = Effekseer::Manager::Create( 255 );

	// �`��p�C���X�^���X����`��@�\��ݒ�
	g_effectManager->SetSpriteRenderer( g_effectRender->CreateSpriteRenderer() );
	g_effectManager->SetRibbonRenderer( g_effectRender->CreateRibbonRenderer() );
	g_effectManager->SetRingRenderer( g_effectRender->CreateRingRenderer() );
	g_effectManager->SetTrackRenderer( g_effectRender->CreateTrackRenderer() );
	g_effectManager->SetModelRenderer( g_effectRender->CreateModelRenderer() );

	// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
	// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
	g_effectManager->SetTextureLoader( g_effectRender->CreateTextureLoader() );
	g_effectManager->SetModelLoader( g_effectRender->CreateModelLoader() );
}

void UpdateEffekseer(){
	//Effekseer�J�����s���ݒ�B
	//�܂���Effeseer�̍s��^�̕ϐ��ɁA�J�����s��ƃv���W�F�N�V�����s����R�s�[�B
	Effekseer::Matrix44 efCameraMat;
	g_camera3D.GetViewMatrix().CopyTo( efCameraMat.Values[0] );
	Effekseer::Matrix44 efProjMat;
	g_camera3D.GetProjectionMatrix().CopyTo( efProjMat.Values[0] );
	//�J�����s��ƃv���W�F�N�V�����s���ݒ�B
	g_effectRender->SetCameraMatrix( efCameraMat );
	g_effectRender->SetProjectionMatrix( efProjMat );
	//Effekseer���X�V�B
	g_effectManager->Update();
}