#pragma once
#include "graphics/IRenderObject.h"
#include "graphics/CFont.h"
#include "graphics/Sprite.h"

/// <summary>
/// �����ŏ�����e�L�X�g
/// </summary>
class DisplayText : public IRenderObject{
public:
	~DisplayText();

	/// <summary>
	/// �e�L�X�g��\������B
	/// </summary>
	/// <param name="text"></param>
	static void display( const wchar_t* text);

	void Render() override;

private:
	//�V���O���g���Ȃ̂ő�������̐����͋֎~
	DisplayText();
	//�V���O���g���擾�֐�
	static DisplayText& Me();

	//�\������
	static constexpr float c_dispTime = 5;
	//�t�F�[�h�C���E�A�E�g�ɂ����鎞��
	static constexpr float fadeSpeed = 1;

	//�c��\������
	float m_dispTime = 0;
	//�e�L�X�g
	const wchar_t* m_text;

	CFont m_font;
	Sprite m_backImage;
};

