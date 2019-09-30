#pragma once
#include "DirectXTK/Inc/SpriteFont.h"

class CFont {
public:
	CFont(const wchar_t* path);
	~CFont();

	void Begine();
	void End();
	void DrawStr(const wchar_t* str);

private:
	DirectX::SpriteFont m_font;
};