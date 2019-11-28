#include "stdafx.h"
#include "Title.h"
#include "graphics/SpriteRender.h"
#include "Scene/Stage1.h"

Title::Title() {
	backImage.Init(L"Assets/sprite/Title_back.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
}

Title::~Title() {
}

void Title::Update() {
	if (g_pad->IsTrigger(enButtonA)) {
		NewGO<Stage1>(0);
		DeleteGO(this);
	}
}
