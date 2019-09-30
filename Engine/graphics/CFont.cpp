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
	m_font.DrawString(GetSpriteBatch(), str, DirectX::XMFLOAT2(0, 0));
}
