#include "stdafx.h"
#include "Title.h"
#include "graphics/SpriteRender.h"
#include "Scene/Stage1.h"
#include "Util/Fade.h"

Title::Title() {
	backImage.Init(L"Assets/sprite/Title_back.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	Fade::Out();
}

Title::~Title() {
}

void Title::Update() {
	if (g_pad->IsTrigger(enButtonA)) {
		Fade::In( [&](){
			NewGO<Stage1>( 0 );
			DeleteGO( this );
		} );
	}
}
