#include "stdafx.h"
#include "FontRender.h"
#include "RenderObjectManager.h"

FontRender::FontRender() : m_font(L"Assets/font/font.spritefont"){
	g_ROManager.AddHUDRender( this );
}

FontRender::~FontRender(){}

void FontRender::Render(){
	m_font.Begine();

	m_font.DrawStr( m_text );

	m_font.End();
}
