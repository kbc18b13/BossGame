#pragma once
class SoundOverlap{
public:
	~SoundOverlap();

	void Init( const wchar_t* filepath ){
		m_filepath = filepath;
	}
	void Play();

private:
	const wchar_t* m_filepath = nullptr;
	std::vector<std::unique_ptr<CSoundSource>> m_sounds;
};

