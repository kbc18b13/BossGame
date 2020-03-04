#pragma once
#include "graphics/Sprite.h"
#include "graphics/IRenderObject.h"

class MiniBarGauge : public IRenderObject{
public:
	MiniBarGauge();
	~MiniBarGauge();

	//������
	void Init( const wchar_t* outImagePath, const wchar_t* inImagePath, UINT width, UINT height );

	//�Q�[�W�̊�����ݒ�
	void SetPercent( float per ){
		m_percent = per;
	}

	//�ʒu��ݒ�
	void SetPos( const CVector3 pos ){
		m_pos = pos;
	}

	void SetColor( const CVector4& color ){
		m_in.SetMulColor( color );
	}

	void view();

	void Render() override;

	void SetActive( bool active ){
		m_active = active;
	}

private:
	static constexpr float c_time = 3.0f;
	float time = 0.0f;

	Sprite m_out;//�O���摜
	Sprite m_in;//�����摜
	float m_percent = 1.0f;//����
	CVector3 m_pos;//�ʒu
	bool m_active = true;
};

