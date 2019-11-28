#include "stdafx.h"
#include "SkinModelRender.h"
#include "RenderObjectManager.h"

SkinModelRender::SkinModelRender(){}


SkinModelRender::~SkinModelRender(){
    if(m_isShadowCaster)g_ROManager.RemoveShadowCaster( this );
}

void SkinModelRender::Init( const wchar_t * filePath,
                            AnimationClip animClipList[],
                            int numAnimClip,
                            EnFbxUpAxis enFbxUpAxis,
                            bool isShadowCaster ){
    m_skinModel.Init( filePath, enFbxUpAxis );
    if( numAnimClip != 0 ){
        m_animation.Init( m_skinModel, animClipList, numAnimClip );
    }

    if( isShadowCaster ){
        g_ROManager.AddShadowCaster( this );
        m_isShadowCaster = true;
    }
    g_ROManager.AddDefaultRender( this );
}

void SkinModelRender::Update(){
    m_animation.Update( GameTime::GetDeltaTime() );
    m_skinModel.UpdateWorldMatrix( m_pos, m_rot, m_scale );
}

void SkinModelRender::Render(){
    m_skinModel.Draw(
        g_camera3D.GetViewMatrix(),
        g_camera3D.GetProjectionMatrix()
    );
}

void SkinModelRender::SetWorldMatrix( const CMatrix & wMat ){
    m_pos = CVector3( wMat.v[3] );
    float x = wMat.v[0].Length();
    float y = wMat.v[1].Length();
    float z = wMat.v[2].Length();
    m_scale = CVector3( x, y, z );
    m_rot.SetRotation( wMat );
}
