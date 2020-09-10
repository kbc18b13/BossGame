#include "stdafx.h"
#include "SkinModelRender.h"
#include "RenderObjectManager.h"

SkinModelRender::SkinModelRender(){}


SkinModelRender::~SkinModelRender(){
	if( m_isShadowCaster )g_ROManager.RemoveShadowCaster( this );
}

void SkinModelRender::Init(const SkinModelRenderInitParam&  p){
	m_skinModel.Init( p.filePath, p.enFbxUpAxis );
	if( p.numAnimClip != 0 ){
		m_animation.Init( m_skinModel, p.animClipList, p.numAnimClip );
	}

	if( p.isStencliDraw ){
		g_ROManager.AddStencilRender( this );
		m_skinModel.SetStencilRef( 1 );
		return;
	}

	if( p.isShadowCaster ){
		g_ROManager.AddShadowCaster( this );
		m_isShadowCaster = true;
	}

	if( p.isAlpha ){
		g_ROManager.AddTranslucentRender( this );
	} else{
		g_ROManager.AddDefaultRender( this );
	}
}

void SkinModelRender::Update(){
	if( m_isActive ){
		m_animation.Update( GameTime::GetDeltaTime() * m_animSpeed );
		m_skinModel.UpdateWorldMatrix( m_pos, m_rot, m_scale );
	}
}

void SkinModelRender::Render( EnRenderMode renderMode, CMatrix viewMatrix, CMatrix projMatrix ){
	if( m_isActive ){
		m_skinModel.Draw(
			renderMode,
			viewMatrix,
			projMatrix
		);
	}
}

void SkinModelRender::SetWorldMatrix( const CMatrix & wMat ){
	m_pos = CVector3( wMat.v [3] );
	float x = wMat.v [0].Length();
	float y = wMat.v [1].Length();
	float z = wMat.v [2].Length();
	m_scale = CVector3( x, y, z );
	m_rot.SetRotation( wMat );
}
