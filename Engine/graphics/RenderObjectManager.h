#pragma once
#include "RenderTarget.h"
#include "ShadowMap.h"
#include "RenderMachine.h"
#include "PostEffect/PostEffect.h"
#include "PostEffect/Blur.h"

class RenderObjectManager;

extern RenderObjectManager g_ROManager;

class RenderObjectManager{
public:
    RenderObjectManager();
    ~RenderObjectManager();

    //�������B
    void Init();

    //�`��B
    void Render();

    //���ʂ̕`��I�u�W�F�N�g�̓o�^
    void AddDefaultRender( IRenderObject* ro ){
        ro->machine = &m_defaultRender;
        m_defaultRender.AddRenderObject( ro );
    }

    //�V���h�E�L���X�^�[��o�^
    void AddShadowCaster( SkinModelRender* modelRender ){
        m_shadowMap.AddShadowCaster( modelRender );
    }

    void RemoveShadowCaster( SkinModelRender* modelRender ){
        m_shadowMap.RemoveShadowCaster( modelRender );
    }

    //HUD�`��I�u�W�F�N�g�̓o�^
    void AddHUDRender( IRenderObject* ro ){
        ro->machine = &m_HUDRender;
        m_HUDRender.AddRenderObject( ro );
    }

    //�V���h�E�}�b�v���擾
    ShadowMap& GetShadowMap(){
        return m_shadowMap;
    }

private:
    //�`���
    RenderTarget m_defaultTarget;

    //�V���h�E�}�b�v
    ShadowMap m_shadowMap;

    //�`��I�u�W�F�N�g
    RenderMachine m_defaultRender;
    RenderMachine m_HUDRender;

    //�|�X�g�G�t�F�N�g
    PostEffect m_postEffect;
    Shader m_monoShader;
    Blur m_blur;
};

