#pragma once
#include "graphics/Sprite.h"
#include "graphics/IRenderObject.h"

class MiniBarGauge : public IRenderObject{
public:
	MiniBarGauge();
	~MiniBarGauge();

	//初期化
	void Init( const wchar_t* outImagePath, const wchar_t* inImagePath, UINT width, UINT height );

	//ゲージの割合を設定
	void SetPercent( float per ){
		m_percent = per;
	}

	//位置を設定
	void SetPos( const CVector3 pos ){
		m_pos = pos;
	}

	void SetColor( const CVector4& color ){
		m_in.SetMulColor( color );
	}

	void view();

	void Render() override;

	void SetActive( bool active ){
		m_active = active;
	}

private:
	static constexpr float c_time = 3.0f;
	float time = 0.0f;

	Sprite m_out;//外側画像
	Sprite m_in;//内側画像
	float m_percent = 1.0f;//割合
	CVector3 m_pos;//位置
	bool m_active = true;
};

