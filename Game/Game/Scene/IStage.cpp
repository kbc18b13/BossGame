#include "stdafx.h"
#include "IStage.h"
#include "Actor/Player/Player.h"

IStage::IStage(){}


IStage::~IStage(){
	DeleteGO( player );
	for( Actor* e : enemyArray ){
		DeleteGO( e );
	}
}
