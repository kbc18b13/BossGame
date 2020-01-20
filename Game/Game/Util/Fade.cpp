#include "stdafx.h"
#include "Fade.h"
#include "graphics//RenderObjectManager.h"

Fade::Fade(){
	m_sprite.Init( L"Assets/sprite/fade.dds", FRAME_BUFFER_W, FRAME_BUFFER_H );
	g_ROManager.AddHUDRender(this);
}

Fade::~Fade(){}

Fade& Fade::Me(){
	static Fade st_fade;
	return st_fade;
}

void Fade::Render(){
	if( m_state == FState::In ){
		m_alpha += GameTime::GetDeltaTime();
		if( m_alpha >= 1.0f ){
			m_state = FState::Idle;
			m_func();
			m_func = nullptr;
		}
	}
	if( m_state == FState::Out ){
		m_alpha -= GameTime::GetDeltaTime();
		if( m_alpha <= 0.0f ){
			m_state = FState::Idle;
		}
	}
	m_sprite.SetMulColor( CVector4( 1, 1, 1, m_alpha ) );
	m_sprite.Draw();
}
