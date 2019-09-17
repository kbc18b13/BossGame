#include "stdafx.h"
#include "Stage1.h"
#include "Actor/Player/Player.h"
#include "Actor/Enemy/Troll.h"

Stage1::Stage1() {
	p = NewGO<Player>(0);
	t = NewGO<Troll>(0);
}

Stage1::~Stage1() {
	DeleteGO(p);
	DeleteGO(t);
}

void Stage1::Update() {
}
