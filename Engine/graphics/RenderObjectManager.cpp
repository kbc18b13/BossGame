#include "stdafx.h"
#include "RenderObjectManager.h"

RenderObjectManager g_ROManager;

RenderObjectManager::RenderObjectManager(){}


RenderObjectManager::~RenderObjectManager(){}

void RenderObjectManager::Init(){
    m_shadowMap.Init( 2048, 2048 );
    m_postEffect.Init();

    //�|�X�g�G�t�F�N�g�O�ɏ������ރ����_�����O�^�[�Q�b�g
    m_defaultTarget.Init( FRAME_BUFFER_W, FRAME_BUFFER_H, DXGI_FORMAT_R8G8B8A8_UNORM );

    //���m�N���V�F�[�_�[
    m_monoShader.Load( "Assets/shader/monochrome.fx", "PSMain", Shader::EnType::PS );
}

void RenderObjectManager::Render(){
    ID3D11DeviceContext* dc = g_graphicsEngine->GetD3DDeviceContext();

    //�V���h�E�}�b�v�̕`��B
    m_shadowMap.RenderToShadowMap( dc );

    //�`����ʏ�^�[�Q�b�g�ցB
    m_defaultTarget.SetToContext( dc );
    m_defaultTarget.Clear(CVector4(0, 0, 0, 1));

    //�ʏ�`��I�u�W�F�N�g�̕`��
    m_defaultRender.Render();

    //�������C���[�t���[��
    g_physics.DebugDraw();

    //�`�����t���[���o�b�t�@�ցB
    g_graphicsEngine->BegineFrameBuffer();

    //�|�X�g�G�t�F�N�g�K�p�B
    m_postEffect.DrawScreenRect((ID3D11PixelShader*)m_monoShader.GetBody(), m_defaultTarget.GetRenderTargetSRV());

    //HUD�`��I�u�W�F�N�g�̕`��B
    m_HUDRender.Render();
}
