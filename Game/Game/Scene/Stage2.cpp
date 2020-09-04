#include "stdafx.h"
#include "Stage2.h"
#include "level/Level.h"
#include "Actor/Enemy/Archer/Archer.h"
#include "Actor/Enemy/Skeleton/SkeletonEnemy.h"
#include "Actor/Enemy/Slime/Slime.h"

Stage2::Stage2( StageManager* manager ) : ground( L"Assets/modelData/SecondStage.cmo" ), IStage(manager){
	Level level;
	level.Init( L"Assets/level/level2.tkl", [&]( LevelObjectData& objData ) -> bool{
		if( wcscmp( objData.name, L"Stage2" ) == 0 ){
			ground.SetPos( objData.position );
		}
		if( wcscmp( objData.name, L"Skeleton" ) == 0 ){
			Actor* t = NewGO<SkeletonEnemy>( 0, this );
			t->SetPos( objData.position );
			enemyArray.push_back( t );
		}
		if( wcscmp( objData.name, L"Archer" ) == 0 ){
			Actor* t = NewGO<EnemySpace::Archer>( 0, this );
			t->SetPos( objData.position );
			enemyArray.push_back( t );
		}
		if( wcscmp( objData.name, L"Slime" ) == 0 ){
			Actor* t = NewGO<Slime>( 0, this );
			t->SetPos( objData.position );
			enemyArray.push_back( t );

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
	for( auto e : enemyArray ){
		e->SetStencilRef( ref );
	}
}
