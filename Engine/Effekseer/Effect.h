#pragma once
extern EffekseerRenderer::Renderer* g_effectRenderr;
extern Effekseer::Manager* g_effectManager;

namespace MyEngine{

class Effect{
public:
	~Effect(){

	}

	void Init( const wchar_t* filepath , float scale = 1){
		m_effect = Effekseer::Effect::Create( g_effectManager, (const EFK_CHAR*)filepath, scale );
	}

	void Play(){
		m_hundle = g_effectManager->Play( m_effect, m_pos );
	}

	void SetRot(){
		
	}

private:
	Effekseer::Handle m_hundle;
	Effekseer::Vector3D m_pos;
	Effekseer::Effect* m_effect;
};

}

