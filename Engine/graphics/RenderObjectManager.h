#pragma once
#include "RenderTarget.h"
#include "ShadowMap.h"
#include "CascadeShadow.h"
#include "RenderMachine.h"
#include "PostEffect/PostEffect.h"
#include "PostEffect/Bloom.h"

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

	//�X�e���V���`��p�I�u�W�F�N�g�̓o�^
	void AddStencilRender( IRenderObject* ro ){
		m_stencilRender.AddRenderObject( ro );
	}

	//��`��p�I�u�W�F�N�g�̓o�^
	void AddSkyRender( IRenderObject* ro ){
		m_skyRender.AddRenderObject( ro );
	}

    //���ʂ̕`��I�u�W�F�N�g�̓o�^
    void AddDefaultRender( IRenderObject* ro ){
        m_defaultRender.AddRenderObject( ro );
    }

	//�������I�u�W�F�N�g�̓o�^
	void AddTranslucentRender( IRenderObject* ro ){
		m_translucentRender.AddRenderObject( ro );
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
        m_HUDRender.AddRenderObject( ro );
    }

	//�t�F�[�h�`��I�u�W�F�N�g�̓o�^
	void SetFadeRender( IRenderObject* ro ){
		m_fadeRender = ro;
	}

    //�V���h�E�}�b�v���擾
    CascadeShadow& GetShadowMap(){
        return m_shadowMap;
    }

private:
    //�`���
    RenderTarget m_defaultTarget;

    //�V���h�E�}�b�v
    //ShadowMap m_shadowMap;
	CascadeShadow m_shadowMap;

    //�`��I�u�W�F�N�g
	RenderMachine m_stencilRender;
	RenderMachine m_skyRender;
    RenderMachine m_defaultRender;
	RenderMachine m_translucentRender;
    RenderMachine m_HUDRender;

	IRenderObject* m_fadeRender = nullptr;

    //�|�X�g�G�t�F�N�g
    PostEffect m_postEffect;
    Shader m_monoShader;
	Bloom m_bloom;

	ComPtr<ID3D11DepthStencilState> m_noDepth; //�[�x�����X�e�[�g
	ComPtr<ID3D11DepthStencilState> m_stencilStateR;//�X�e���V���p�ǂݍ��݃X�e�[�g
	ComPtr<ID3D11DepthStencilState> m_stencilStateW;//�X�e���V���p�������݃X�e�[�g

	ComPtr<ID3D11BlendState> m_alphaBlend;
};

