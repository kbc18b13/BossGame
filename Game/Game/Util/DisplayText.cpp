#include "stdafx.h"
#include "DisplayText.h"
#include "graphics/RenderObjectManager.h"

DisplayText::DisplayText() : m_font( L"Assets/font/font.spritefont" ){
	m_font.SetPos( CVector2( 640, 360 ) );
	m_font.SetPivot( CVector2( 0.5f, 0.5f ) );
	m_font.SetScale( CVector2( 3, 3 ) );

	m_backImage.Init( L"Assets/sprite/TextBack.dds", 1190, 250 );
	m_backImage.UpdateWorldMatrix( CVector2( 0, 0 ), CVector2::One(), CQuaternion::Identity() );

	g_ROManager.AddHUDRender( this );
}

DisplayText::~DisplayText(){}

DisplayText& DisplayText::Me(){
	static DisplayText st_dispText;
	return st_dispText;
}


void DisplayText::display( const wchar_t * text ){
	Me().m_text = text;
	Me().m_dispTime = c_dispTime;
}

void DisplayText::Render(){
	//表示時間が残ってなければ何もしない
	if( m_dispTime <= 0 ){
		return;
	}

	//フェードイン・アウト
	float alpha;
	if( m_dispTime > fadeSpeed ){
		alpha = std::min( c_dispTime - m_dispTime, fadeSpeed ) / fadeSpeed;
	} else{
		alpha = m_dispTime / fadeSpeed;
	}

	m_backImage.SetMulColor( CVector4( 1, 1, 1, alpha ) );

	m_backImage.Draw();

	m_font.Begine();

	m_font.SetColor( CVector4( 0.5f, 0.5f, 1, alpha) );

	m_font.DrawStr( m_text );

	m_font.End();

	//表示残り時間減少
	m_dispTime -= GameTime::GetDeltaTime();
}
