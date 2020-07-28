#include "stdafx.h"
#include "Stage2.h"
#include "level/Level.h"

Stage2::Stage2() : ground( L"Assets/modelData/SecondStage.cmo" ) {

	Level level;
	level.Init( L"Assets/level/level.tkl", [&]( LevelObjectData& objData ) -> bool{
		if( wcscmp( objData.name, L"Stage2" ) == 0 ){
			ground.SetPos( objData.position );
		}
		return true;
	} );

	sky.Init( L"Assets/modelData/sky2.cmo" );
	sky.SetRot( CQuaternion::CreateRotDeg( CVector3::AxisY(), 180 ) );

	SetStageStencilRef( 1 );
}

Stage2::~Stage2(){}

void Stage2::Update(){}

void Stage2::SetStageStencilRef( int ref ){
	ground.GetModel()->GetModel().SetStencilRef( ref );
	sky.SetStencilRef( ref );
}
