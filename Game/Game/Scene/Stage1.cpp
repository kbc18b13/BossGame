#include "stdafx.h"
#include "level/Level.h"
#include "Stage1.h"
#include "Actor/Player/Player.h"
#include "Actor/Enemy/Troll/Troll.h"
#include "Actor/Enemy/Skeleton/SkeletonEnemy.h"
#include "Actor/Enemy/Yowai/Yowai.h"
#include "Actor/Enemy/Slime/Slime.h"
#include "Title.h"
#include "Util/Fade.h"

//地形などの読み込み
Stage1::Stage1() : ground( L"Assets/modelData/FirstStage.cmo" ),
carriage( L"Assets/modelData/Carriage.cmo", L"Assets/modelData/Carriage_col.cmo" ){

	//各種オブジェクトの配置。
	Level level;
	level.Init( L"Assets/level/level.tkl", [&]( LevelObjectData& objData ) -> bool{
		if( wcscmp( objData.name, L"Stage" ) == 0 ){
			ground.SetPos( objData.position );

		} else if( wcscmp( objData.name, L"Chara" ) == 0 ){
			player = NewGO<Player>( 0, this );
			player->SetPos( objData.position );
			player->SetStage( this );

		} else if( wcscmp( objData.name, L"Troll" ) == 0 ){
			trollPos = objData.position;

		} else if( wcscmp( objData.name, L"Carriage" ) == 0 ){
			carriage.SetPos( objData.position );
			carriage.SetRot( objData.rotation );

		} else if( wcscmp( objData.name, L"BigDoor" ) == 0 ){
			bigDoor = NewGO<BigDoor>( 0 );
			bigDoor->SetPos( objData.position );

		} else if( wcscmp( objData.name, L"Skeleton" ) == 0 ){
			Actor* t = NewGO<SkeletonEnemy>( 0, this );
			t->SetPos( objData.position );
			enemyArray.push_back( t );

		} else if( wcscmp( objData.name, L"Yowai" ) == 0 ){
			Yowai* t = NewGO<Yowai>( 0, this );
			t->SetPos( objData.position );
			t->SetOpener( &opener );
			opener.AddEnemyCount();
			enemyArray.push_back( t );

		} else if( wcscmp( objData.name, L"Slime" ) == 0){
			/*Actor* a = NewGO<Slime>( 0, this );
			a->SetPos( objData.position );
			enemyArray.push_back( a );*/

		} else if( wcscmp( objData.name, L"BossRoom" ) == 0 ){
			std::function<void()> f = [&](){
				Actor* t = NewGO<Troll>( 0, this );
				t->SetPos( trollPos );
				enemyArray.push_back( t );
				DeleteGO( bossRoomTrigger );
				bossRoomTrigger = nullptr;

			};

			bossRoomTrigger = NewGO<TriggerCollision>( 0 );
			bossRoomTrigger->Init( f, CVector3( 125, 125, 125 ), objData.position, objData.rotation );
		}
		return true;
	} );

	opener.SetDoor( bigDoor );

	wpManager.Load( L"Assets/level/wayPoint.wpdata" );

	g_graphicsEngine->GetDirectionLight().SetColor( 0, { 1,1,1,1 } );
	g_graphicsEngine->GetDirectionLight().SetDirection( 0, { -1,-1,-1 } );
	g_graphicsEngine->GetDirectionLight().Apply();

	g_graphicsEngine->GetAmbientLight().SetColor( { 0.5f,0.5f,0.5f,1 } );
	g_graphicsEngine->GetAmbientLight().Apply();

	Fade::Out();
}

Stage1::~Stage1(){
	if( bossRoomTrigger )
		DeleteGO( bossRoomTrigger );
	DeleteGO( bigDoor );
}

void Stage1::Update(){
	if( g_pad->IsTrigger( enButtonUp ) ){
		bigDoor->Open();
	}
	if( g_pad->IsTrigger( enButtonDown ) ){
		bigDoor->Close();
	}

	//ステージ終了処理
	if( isEndStage ){
		endTime += GameTime::GetDeltaTime();

		if( endTime >= 6 ){
			Fade::In( [&](){
				DeleteGO( this );
				NewGO<Title>( 0 );
			} );
		}
	}
}

void Stage1::EndStage(){
	isEndStage = true;
}
