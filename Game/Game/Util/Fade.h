#pragma once
#include "graphics/IRenderObject.h"
#include "graphics/Sprite.h"
class Fade : public IRenderObject{
public:
	~Fade();

	static void In(const std::function<void()>& func ){
		Me().m_func = func;
		Me().m_state = FState::In;
	}

	static void Out(){
		Me().m_state = FState::Out;
	}

	void Render() override;

private:
	//シングルトンなので他所からの生成は禁止
	Fade();
	//シングルトン取得関数
	static Fade& Me();

	enum class FState{
		In,
		Idle,
		Out,
	};

	std::function<void()> m_func;

	float m_alpha = 1.0f;

	FState m_state = FState::Out;
	Sprite m_sprite;
};

