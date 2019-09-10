#pragma once
#include "SpriteEffect.h"

class Sprite {
public:
	Sprite();
	~Sprite();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="path">�e�N�X�`���p�X</param>
	/// <param name="width">��</param>
	/// <param name="hight">����</param>
	void Init(const wchar_t* path, UINT width, UINT height);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/*!
	*@brief	���f�������[���h���W�n�ɕϊ����邽�߂̃��[���h�s����X�V����B
	*@param[in]	position	���f���̍��W�B
	*@param[in]	rotation	���f���̉�]�B
	*@param[in]	scale		���f���̊g�嗦�B
	*/
	void UpdateWorldMatrix(const CVector2& pos, const CVector2& scale, const CQuaternion& rot);

	/*!
	*@brief	���f�������[���h���W�n�ɕϊ����邽�߂̃��[���h�s����X�V����B
	*@param[in]	mat        ���f���̃��[���h���W	
	*/
	void UpdateWorldMatrix(const CMatrix& mat) {
		m_worldMat = mat;
	}

private:
	SpriteEffect m_effect;                    //�e�N�X�`����V�F�[�_�[�Ȃ�
	ID3D11Buffer* m_vertex;                   //���_�o�b�t�@
	CMatrix m_worldMat = CMatrix::Identity(); //���[���h�s��(CPU)
	ID3D11Buffer* m_worldMatBuf;              //���[���h�s��(GPU)
};

