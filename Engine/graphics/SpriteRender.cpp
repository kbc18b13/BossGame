#include "stdafx.h"
#include "SpriteRender.h"
#include "RenderObjectManager.h"

void SpriteRender::Render() {
    m_sprite.UpdateWorldMatrix(m_pos, m_scale, m_rot, m_pivot);
	m_sprite.Draw();
}

void SpriteRender::Init(const wchar_t * path, UINT width, UINT height) {
	m_sprite.Init(path, width, height);
    g_ROManager.AddHUDRender( this );
}
