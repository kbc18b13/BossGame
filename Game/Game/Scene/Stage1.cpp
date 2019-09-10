#include "stdafx.h"
#include "Stage1.h"
#include "Actor/Player/Player.h"

Stage1::Stage1() {
	p = GOManager().NewGO<Player>(0);
}

Stage1::~Stage1() {
	GOManager().DeleteGO(p);
}

void Stage1::Update() {
}
