#include "stdafx.h"
#include "level/Level.h"
#include "Stage1.h"
#include "Actor/Player/Player.h"
#include "Actor/Enemy/Troll.h"


Stage1::Stage1() {
	Level level;
	level.Init(L"Assets/level/level.tkl", [&](LevelObjectData& objData) -> bool {
		if (wcscmp(objData.name, L"Stage") == 0) {
			g.SetPos(objData.position);
		} else if (wcscmp(objData.name, L"Chara")) {
			p = NewGO<Player>(0);
			p->SetPos(objData.position);
		} else if (wcscmp(objData.name, L"Troll")) {
			t = NewGO<Troll>(0);
			t->SetPos(objData.position);
		}
		return true;
	});
	g_graphicsEngine->GetDirectionLight().SetColor(    0, { 1,1,1,1 });
	g_graphicsEngine->GetDirectionLight().SetDirection(0, { -1,-1,-1});
	g_graphicsEngine->GetDirectionLight().SetColor(    1, { 0.2f,0.2f,0.2f,1 });
	g_graphicsEngine->GetDirectionLight().SetDirection(1, { 1,1,1 });
	g_graphicsEngine->GetDirectionLight().Apply();
}

Stage1::~Stage1() {
	DeleteGO(p);
	DeleteGO(t);
}

void Stage1::Update() {
}
