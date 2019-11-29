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

    //初期化。
    void Init();

    //描画。
    void Render();

    //普通の描画オブジェクトの登録
    void AddDefaultRender( IRenderObject* ro ){
        ro->machine = &m_defaultRender;
        m_defaultRender.AddRenderObject( ro );
    }

    //シャドウキャスターを登録
    void AddShadowCaster( SkinModelRender* modelRender ){
        m_shadowMap.AddShadowCaster( modelRender );
    }

    void RemoveShadowCaster( SkinModelRender* modelRender ){
        m_shadowMap.RemoveShadowCaster( modelRender );
    }

    //HUD描画オブジェクトの登録
    void AddHUDRender( IRenderObject* ro ){
        ro->machine = &m_HUDRender;
        m_HUDRender.AddRenderObject( ro );
    }

    //シャドウマップを取得
    ShadowMap& GetShadowMap(){
        return m_shadowMap;
    }

private:
    //描画先
    RenderTarget m_defaultTarget;

    //シャドウマップ
    ShadowMap m_shadowMap;

    //描画オブジェクト
    RenderMachine m_defaultRender;
    RenderMachine m_HUDRender;

    //ポストエフェクト
    PostEffect m_postEffect;
    Shader m_monoShader;
    Blur m_blur;
};

