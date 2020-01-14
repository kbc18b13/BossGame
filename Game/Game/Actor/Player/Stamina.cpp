#include "stdafx.h"
#include "Stamina.h"

static constexpr float c_recoverCool = 1;

Stamina::Stamina(){
	m_stamina = m_maxStamina;

	m_gauge.Init( L"Assets/sprite/HpOut.dds", L"Assets/sprite/HpIn.dds", 1000, 25 );
	m_gauge.SetPosLikeTex( CVector2( 1255, 110 ) );
}

Stamina::~Stamina(){}

void Stamina::Update(){
	if( m_recoverCool > 0 ){
		m_recoverCool -= GameTime::GetDeltaTime();
	} else{
		m_stamina = std::min(m_stamina + GameTime::GetDeltaTime() * 5 , m_maxStamina);
	}
	m_gauge.SetPercent( m_stamina / m_maxStamina );
}

bool Stamina::Consume( UINT amount ){
	if( amount == 0 ){
		return true;
	}else if( m_stamina >= amount ){
		m_stamina -= amount;
		m_recoverCool = c_recoverCool;
		return true;
	}
	return false;
}
