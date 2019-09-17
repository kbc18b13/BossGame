#include "stdafx.h"
#include "Stage1.h"
#include "Actor/Player/Player.h"

Stage1::Stage1() {
	p = NewGO<Player>(0);
}

Stage1::~Stage1() {
	DeleteGO(p);
}

void Stage1::Update() {
}
