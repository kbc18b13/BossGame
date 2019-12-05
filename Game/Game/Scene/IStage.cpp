#include "stdafx.h"
#include "IStage.h"


IStage::IStage(){}


IStage::~IStage(){
	for( Actor* e : enemyArray ){
		DeleteGO( e );
	}
}
