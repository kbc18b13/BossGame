#include "stdafx.h"
#include "LongPressButton.h"

void LongPressButton::Update(){
	m_isTrigger = false;

	if( g_pad->IsTrigger( m_button ) ){
		m_timer = c_timer;
	}

	if( g_pad->IsPress( m_button ) ){
		m_timer -= GameTime::GetDeltaTime();
		m_isPress = true;

	} else if(m_isPress){
		if( m_timer > 0 ){
			m_isTrigger = true;
		}
		m_isPress = false;
	}
}
