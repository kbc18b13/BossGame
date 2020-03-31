#include "stdafx.h"
#include "SoundOverlap.h"

SoundOverlap::~SoundOverlap(){
}

void SoundOverlap::Play(){
	//再生が終わったサウンドを破棄
	auto end = std::remove_if(m_sounds.begin(), m_sounds.end(),
							   [](std::unique_ptr<CSoundSource>& s )->bool{return !s->IsPlaying(); } );
	m_sounds.erase( end, m_sounds.end() );

	//新しいサウンドソースで再生
	CSoundSource* sound = new CSoundSource;
	sound->Init( m_filepath );
	sound->Play( false );
	m_sounds.push_back( std::unique_ptr<CSoundSource>(sound) );
}
