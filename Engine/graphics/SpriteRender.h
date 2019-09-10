#include "Sprite.h"

class SpriteRender : public IGameObject {
public:
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��֐�
	/// </summary>
	void Draw() override;

	/// <summary>
	/// �������֐�
	/// </summary>
	/// <param name="path">dds�̃t�@�C���p�X</param>
	void Init(const wchar_t* path, UINT width, UINT height);

	/// <summary>
	/// �ʒu��ݒ�
	/// </summary>
	/// <param name="pos">�ʒu�B�s�N�Z���P�ʁB</param>
	void SetPos(const CVector2& pos) {
		m_pos = pos;
	}

	/// <summary>
	/// �ʒu���擾
	/// </summary>
	/// <returns></returns>
	CVector2 GetPos() {
		return m_pos;
	}

	/// <summary>
	/// �g�嗦��ݒ�
	/// </summary>
	/// <param name="scale">�g�嗦�B</param>
	void SetScale(const CVector2& scale) {
		m_scale = scale;
	}

	/// <summary>
	/// �g�嗦���擾
	/// </summary>
	/// <returns></returns>
	CVector2 GetScale() {
		return m_scale;
	}

	/// <summary>
	/// ��]��ݒ�
	/// </summary>
	/// <param name="rot">��]�N�H�[�^�j�I��</param>
	void SetRot(const CQuaternion& rot) {
		m_rot = rot;
	}

	/// <summary>
	/// ��]���擾
	/// </summary>
	/// <returns></returns>
	CQuaternion GetRot() {
		return m_rot;
	}
private:
	CVector2 m_pos = CVector2::Zero();            //�ʒu
	CVector2 m_scale = CVector2::One();           //�g�嗦
	CQuaternion m_rot = CQuaternion::Identity();  //��]
	Sprite m_sprite; //Sprite
};