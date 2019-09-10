#include "stdafx.h"
#include "Title.h"
#include "graphics/SpriteRender.h"

Title::Title() {
	backImage = GOManager().NewGO<SpriteRender>(0);
}

Title::~Title() {
}

void Title::Update() {
}

void Title::Draw() {
}
