#include "stdafx.h"
#include "Title.h"
#include "graphics/SpriteRender.h"
#include "Scene/StageManager.h"
#include "Util/Fade.h"

Title::Title() {
	backImage.Init(L"Assets/sprite/Title_back.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	m_bgm.Init( L"Assets/sound/titleBGM.wav" );
	m_bgm.Play( true );
	Fade::Out();
}

Title::~Title() {
}

void Title::Update() {
	if (g_pad->IsTrigger(enButtonA)) {
		Fade::In( [&](){
			NewGO<StageManager>( 0 );
			DeleteGO( this );
		} );
	}
}
