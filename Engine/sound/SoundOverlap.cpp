#include "stdafx.h"
#include "SoundOverlap.h"

SoundOverlap::~SoundOverlap(){
}

void SoundOverlap::Play(){
	//�Đ����I������T�E���h��j��
	auto end = std::remove_if(m_sounds.begin(), m_sounds.end(),
							   [](std::unique_ptr<CSoundSource>& s )->bool{return !s->IsPlaying(); } );
	m_sounds.erase( end, m_sounds.end() );

	//�V�����T�E���h�\�[�X�ōĐ�
	CSoundSource* sound = new CSoundSource;
	sound->Init( m_filepath );
	sound->Play( false );
	m_sounds.push_back( std::unique_ptr<CSoundSource>(sound) );
}
