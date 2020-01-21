#pragma once
#include "graphics/Sprite.h"
#include "graphics/IRenderObject.h"

class BarGauge : IRenderObject{
public:
	BarGauge();
	~BarGauge();

	//初期化
	void Init( const wchar_t* outImagePath, const wchar_t* inImagePath, UINT width, UINT height );

	//ゲージの割合を設定
	void SetPercent( float per ){
		m_percent = per;
	}

	//中央が0の座標で位置を設定
	void SetPosCenterZero( const CVector2& pos ){
		m_pos = pos;
	}

	//テクスチャ的な座標で位置を設定
	void SetPosLikeTex( const CVector2& pos ){
		m_pos.x = pos.x - (FRAME_BUFFER_W / 2);
		m_pos.y = -(pos.y - ( FRAME_BUFFER_H / 2 ));
	}

	void SetColor( const CVector4& color ){
		m_in.SetMulColor( color );
	}

	void Render() override;

	void SetActive( bool active );

private:
	Sprite m_out;//外側画像
	Sprite m_in;//内側画像
	float m_percent;//割合
	CVector2 m_pos;//位置
	bool m_active = true;
};

