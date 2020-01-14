#pragma once
#include "graphics/IRenderObject.h"
#include "graphics/CFont.h"
#include "graphics/Sprite.h"

/// <summary>
/// 自動で消えるテキスト
/// </summary>
class DisplayText : public IRenderObject{
public:
	~DisplayText();

	/// <summary>
	/// テキストを表示する。
	/// </summary>
	/// <param name="text"></param>
	static void display( const wchar_t* text);

	void Render() override;

private:
	//シングルトンなので他所からの生成は禁止
	DisplayText();
	//シングルトン取得関数
	static DisplayText& Me();

	//表示時間
	static constexpr float c_dispTime = 5;
	//フェードイン・アウトにかける時間
	static constexpr float fadeSpeed = 1;

	//残り表示時間
	float m_dispTime = 0;
	//テキスト
	const wchar_t* m_text;

	CFont m_font;
	Sprite m_backImage;
};

