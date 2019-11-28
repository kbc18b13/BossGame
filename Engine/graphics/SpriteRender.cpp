#include "stdafx.h"
#include "SpriteRender.h"
#include "RenderObjectManager.h"

void SpriteRender::Render() {
    CVector2 pixelPivot = m_pivot;
    pixelPivot.x *= m_sprite.GetWidth() * m_scale.x;
    pixelPivot.y *= m_sprite.GetHeight() * m_scale.y;

    m_sprite.UpdateWorldMatrix(m_pos - pixelPivot, m_scale, m_rot);
	m_sprite.Draw();
}

void SpriteRender::Init(const wchar_t * path, UINT width, UINT height) {
	m_sprite.Init(path, width, height);
    g_ROManager.AddHUDRender( this );
}
