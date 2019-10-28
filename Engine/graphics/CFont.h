#pragma once
#include "DirectXTK/Inc/SpriteFont.h"

class CFont {
public:
	CFont(const wchar_t* path);
	~CFont();

	void Begine();
	void End();
	void DrawStr(const wchar_t* str);

    void SetPivot(const CVector2& piv) {
        m_pivot = piv;
    }

    void SetPos(const CVector2& pos) {
        m_pos = pos;
    }

private:
    CVector2 m_pos;
    CVector2 m_pivot;

	DirectX::SpriteFont m_font;
};