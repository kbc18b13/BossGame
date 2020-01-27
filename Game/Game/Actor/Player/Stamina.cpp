#include "stdafx.h"
#include "Stamina.h"

static constexpr float c_recoverCool = 1;

Stamina::Stamina(){
	m_stamina = m_maxStamina;

	m_gauge.Init( L"Assets/sprite/HpOut.dds", L"Assets/sprite/HpIn.dds", 1000, 25 );
	m_gauge.SetPosLikeTex( CVector2( 1265, 65 ) );
	m_gauge.SetColor( CVector4( 1, 1, 0, 1 ) );
}

Stamina::~Stamina(){}

void Stamina::Update(){
	if( m_recoverCool > 0 ){
		m_recoverCool -= GameTime::GetDeltaTime();
	} else{
		m_stamina = std::min(m_stamina + GameTime::GetDeltaTime() * 10 , m_maxStamina);
	}
	m_gauge.SetPercent( m_stamina / m_maxStamina );
}

bool Stamina::Consume( float amount ){
	if( amount == 0 ){
		return true;
	}

	if( m_stamina > 0 ){
		m_stamina = std::max(m_stamina - amount, 0.f);
		m_recoverCool = c_recoverCool;
		return true;
	}
	return false;
}
