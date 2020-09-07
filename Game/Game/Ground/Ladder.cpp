#include "stdafx.h"
#include "Ladder.h"
#include "Actor/Player/Player.h"
#include "Scene/IStage.h"

Ladder::Ladder() : m_colModel( L"Assets/modelData/Ladder.cmo", L"Assets/modelData/Ladder_Col.cmo" ){}

void Ladder::Update(){
	Player* player = m_stage->GetPlayer();
	if( player->IsOnLadder() ){
		return;
	}

	CVector3 toP = ( player->GetPos() - GetPos() );
	toP.y = 0;
	
	if( toP.LengthSq() < pow2(50) ){
		if( g_pad->IsTrigger( enButtonA ) ){
			player->SetOnLadder(*this);
		}
	}
}
