#include "stdafx.h"

#include "Util/Fade.h"
#include "Title.h"
#include "StageManager.h"
#include "Stage1.h"
#include "Stage2.h"

#include "StageGate.h"

#include "level/Level.h"
#include "Actor/Player/Player.h"

StageManager::StageManager(){
	m_player = NewGO<Player>(0);
	stage2 = NewGO<Stage2>(0, this);
	stage1 = NewGO<Stage1>(0, this);
	m_player->SetStage( stage1 );
	m_player->SetPos( stage1->GetPlayerSpawn() );

	Level level;
	level.Init( L"Assets/level/level.tkl", [&]( LevelObjectData& objData ) -> bool{
		if( wcscmp( objData.name, L"StageGate" ) == 0 ){
			m_gate = NewGO<StageGate>( 0 );
			m_gate->Init( stage1, stage2, GetPlayer() ,objData.position, objData.rotation );
		}
		return true;
	} );
}

void StageManager::Destroy(){
	DeleteGO( stage1 );
	DeleteGO( stage2 );
	DeleteGO( m_player );
	DeleteGO( m_gate );
}

void StageManager::Update(){
	//ステージ終了処理
	if( isEndStage ){
		m_endTime -= GameTime::GetDeltaTime();

		if( m_endTime <= 0 ){
			Fade::In( [&](){
				DeleteGO( this );
				NewGO<Title>( 0 );
			} );
		}
	}
}

