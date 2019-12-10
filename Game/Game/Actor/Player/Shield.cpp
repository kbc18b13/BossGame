#include "stdafx.h"
#include "Shield.h"


Shield::Shield(){}


Shield::~Shield(){}

void Shield::Init( Bone * handBone, Player * p ){
	m_model.Init( L"Assets/modelData/Shield.cmo" );
	m_hand = handBone;
}

void Shield::Update(){
	//ˆÊ’u‚ÌXV
	{
		const CMatrix& worldMat = m_hand->GetWorldMatrix();

		//CQuaternion::CreateRotDeg( 90, CVector3::AxisY );
		//m_collision.GetBody()->getWorldTransform().setRotation( rot );

		///*CVector3 offset = m_offset;
		//rot.Multiply( offset );
		//CVector3 position = CVector3( worldMat.v[3] ) + offset;*/
		//m_collision.GetBody()->getWorldTransform().setOrigin( position );

		m_model.SetWorldMatrix( worldMat );
		m_model.Update();
	}
}
