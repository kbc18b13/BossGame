#include "stdafx.h"
#include "SpriteRender.h"

void SpriteRender::Update() {
	m_sprite.UpdateWorldMatrix(m_pos, m_scale, m_rot);
}

void SpriteRender::Draw() {
	m_sprite.Draw();
}

void SpriteRender::Init(const wchar_t * path, UINT width, UINT height) {
	m_sprite.Init(path, width, height);
}
