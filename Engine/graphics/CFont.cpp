#include "stdafx.h"
#include "CFont.h"

static DirectX::SpriteBatch* GetSpriteBatch() {
	static DirectX::SpriteBatch spriteBatch(g_graphicsEngine->GetD3DDeviceContext());
	return &spriteBatch;
}

CFont::CFont(const wchar_t* path) : m_font(g_graphicsEngine->GetD3DDevice(), path){
}

CFont::~CFont() {
}

void CFont::Begine() {
	GetSpriteBatch()->Begin();
}

void CFont::End() {
	GetSpriteBatch()->End();
}

void CFont::DrawStr(const wchar_t * str) {
    CVector2 pos = m_pos;

    CVector2 pivot;
    DirectX::XMStoreFloat2(&pivot.vec , m_font.MeasureString(str));
    pivot.x *= (m_pivot.x + 0.5f);
    pivot.y *= (m_pivot.y + 0.5f);

    pos -= pivot;

	m_font.DrawString(GetSpriteBatch(), str, pos.vec, CVector4(1,0.5f, 0, 1));
}
