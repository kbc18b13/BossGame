#include "stdafx.h"
#include "Title.h"
#include "graphics/SpriteRender.h"
#include "Scene/Stage1.h"

Title::Title() {
	backImage = NewGO<SpriteRender>(0);
	backImage->Init(L"Assets/sprite/Title_back.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
}

Title::~Title() {
	DeleteGO(backImage);
}

void Title::Update() {
	if (g_pad->IsTrigger(enButtonA)) {
		NewGO<Stage1>(0);
		DeleteGO(this);
	}
}
