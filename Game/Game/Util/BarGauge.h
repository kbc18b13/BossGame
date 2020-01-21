#pragma once
#include "graphics/Sprite.h"
#include "graphics/IRenderObject.h"

class BarGauge : IRenderObject{
public:
	BarGauge();
	~BarGauge();

	//������
	void Init( const wchar_t* outImagePath, const wchar_t* inImagePath, UINT width, UINT height );

	//�Q�[�W�̊�����ݒ�
	void SetPercent( float per ){
		m_percent = per;
	}

	//������0�̍��W�ňʒu��ݒ�
	void SetPosCenterZero( const CVector2& pos ){
		m_pos = pos;
	}

	//�e�N�X�`���I�ȍ��W�ňʒu��ݒ�
	void SetPosLikeTex( const CVector2& pos ){
		m_pos.x = pos.x - (FRAME_BUFFER_W / 2);
		m_pos.y = -(pos.y - ( FRAME_BUFFER_H / 2 ));
	}

	void SetColor( const CVector4& color ){
		m_in.SetMulColor( color );
	}

	void Render() override;

	void SetActive( bool active );

private:
	Sprite m_out;//�O���摜
	Sprite m_in;//�����摜
	float m_percent;//����
	CVector2 m_pos;//�ʒu
	bool m_active = true;
};

