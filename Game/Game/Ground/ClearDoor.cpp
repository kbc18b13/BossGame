#include "stdafx.h"
#include "ClearDoor.h"

void ClearDoor::Update(){
	if( m_clearStart ){
		m_clearTime -= GameTime::GetDeltaTime();

		float alpha = m_clearTime / c_clearTime;

		m_colModel.GetModel()->GetModel().SetAlpha( alpha );

		if( alpha <= 0 ){
			m_clearStart = false;
		}
	}
}
