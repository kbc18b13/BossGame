#pragma once
#include "Ground/CollisionModel.h"
class Ladder{
public:
	Ladder();

	void SetPos( const CVector3& pos ){
		m_colModel.SetPos( pos );
	}

	CVector3 GetPos(){
		return m_colModel.GetPos();
	}

	void SetRot( const CQuaternion& rot ){
		m_colModel.SetRot( rot );
	}

	void SetStencilRef(int ref){
		m_colModel.GetModel()->GetModel().SetStencilRef( ref );
	}

private:
	CollisionModel m_colModel;
};

