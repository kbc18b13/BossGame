#pragma once
#include "Ground/CollisionModel.h"

class IStage;

class Ladder{
public:
	Ladder();

	//毎フレーム呼ぶ必要のある関数。
	void Update();

	void FirstSetting( IStage* stage, const CVector3& pos, const CQuaternion& rot ){
		SetScene( stage ); SetPos( pos ); SetRot( rot );
	}

	void SetScene(IStage* stage){
		m_stage = stage;
	}

	void SetPos( const CVector3& pos ){
		m_colModel.SetPos( pos );
	}

	CVector3 GetPos() const{
		return m_colModel.GetPos();
	}

	void SetRot( const CQuaternion& rot ){
		m_colModel.SetRot( rot );
	}

	CQuaternion GetRot() const{
		return m_colModel.GetRot();
	}

	void SetStencilRef(int ref){
		m_colModel.GetModel()->GetModel().SetStencilRef( ref );
	}

	CVector3 GetFront() const{
		CVector3 v = CVector3::AxisZ();
		m_colModel.GetRot().Multiply( v );
		return v;
	}

	static constexpr float Height = 176;

private:
	IStage* m_stage;
	CollisionModel m_colModel;
};

