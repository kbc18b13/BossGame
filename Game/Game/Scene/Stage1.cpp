#include "stdafx.h"
#include "level/Level.h"
#include "Stage1.h"
#include "Actor/Player/Player.h"
#include "Actor/Enemy/Troll/Troll.h"
#include "Actor/Enemy/Skeleton/SkeletonEnemy.h"
#include "Title.h"

Stage1::Stage1() : ground( L"Assets/modelData/StartStage.cmo" ),
carriage( L"Assets/modelData/Carriage.cmo", L"Assets/modelData/Carriage_col.cmo" ){
	Level level;
	level.Init( L"Assets/level/level.tkl", [&]( LevelObjectData& objData ) -> bool{
		if( wcscmp( objData.name, L"Stage" ) == 0 ){
			ground.SetPos( objData.position );
		} else if( wcscmp( objData.name, L"Chara" ) == 0 ){
			player = NewGO<Player>( 0, this );
			player->SetPos( objData.position + CVector3::Up() * 100 );
			player->SetStage( this );
		} else if( wcscmp( objData.name, L"Troll" ) == 0 ){
			Actor* t = NewGO<Troll>( 0, this );
			t->SetPos( objData.position + CVector3::Up() * 100 );
			enemyArray.push_back( t );
		}
		return true;
	} );

	enemyArray.push_back( NewGO<SkeletonEnemy>( 0, this ) );

	g_graphicsEngine->GetDirectionLight().SetColor( 0, { 1,1,1,1 } );
	g_graphicsEngine->GetDirectionLight().SetDirection( 0, { -1,-1,-1 } );
	//g_graphicsEngine->GetDirectionLight().SetColor(    1, { 0.2f,0.2f,0.2f,1 });
	//g_graphicsEngine->GetDirectionLight().SetDirection(1, { 1,1,1 });
	g_graphicsEngine->GetDirectionLight().Apply();

	g_graphicsEngine->GetAmbientLight().SetColor( { 0.3f,0.3f,0.3f,1 } );
	g_graphicsEngine->GetAmbientLight().Apply();

}

Stage1::~Stage1(){}

void Stage1::Update(){
	if( isEndStage ){
		endTime += GameTime::GetDeltaTime();

		if( endTime >= 6 ){
			DeleteGO( this );
			NewGO<Title>( 0 );
		}
	}
}

void Stage1::EndStage(){
	isEndStage = true;
}
