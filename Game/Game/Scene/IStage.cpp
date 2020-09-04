#include "stdafx.h"
#include "IStage.h"
#include "Actor/Player/Player.h"

IStage::IStage( StageManager* manager ) : manager(manager){
}


IStage::~IStage(){
	for( Actor* e : enemyArray ){
		DeleteGO( e );
	}
}
