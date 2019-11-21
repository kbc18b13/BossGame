#pragma once

/// <summary>
/// ���f���`����s���Q�[���I�u�W�F�N�g�B
/// </summary>
class SkinModelRender : public IGameObject{
public:
	SkinModelRender();
	~SkinModelRender();

	/*!
	*@brief	�������B
	*@param[in]	filePath		���[�h����cmo�t�@�C���̃t�@�C���p�X�B
	*@param[in] enFbxUpAxis		fbx�̏㎲�B�f�t�H���g��enFbxUpAxisZ�B
	*/
	void Init(const wchar_t* filePath,AnimationClip animClipList[] = nullptr, int numAnimClip = 0,
			  EnFbxUpAxis enFbxUpAxis = enFbxUpAxisY);

	/*!
	*@brief	�A�j���[�V�����̍Đ��B
	*@param[in]	clipNo	�A�j���[�V�����N���b�v�̔ԍ��BInit�֐��ɓn����animClipList�̕��тƂȂ�B
	*@param[in]	interpolateTime		�⊮����(�P�ʁF�b)
	*/
	void Play(int clipNo, float interpolateTime = 0.0f) {
		m_animation.Play(clipNo, interpolateTime);
	}

	/*!
	* @brief	�A�j���[�V�����̍Đ����H
	*/
	bool IsPlaying() const {
		return m_animation.IsPlaying();
	}

	/// <summary>
	/// �ʒu��ݒ�
	/// </summary>
	/// <param name="pos">�ʒu</param>
	void SetPos(const CVector3& pos) {
		m_pos = pos;
	}

	/// <summary>
	/// �ʒu���擾
	/// </summary>
	/// <returns></returns>
	CVector3 GetPos() {
		return m_pos;
	}
	
	/// <summary>
	/// �傫����ݒ�
	/// </summary>
	/// <param name="scale">�傫��</param>
	void SetScale(const CVector3& scale) {
		m_scale = scale;
	}

	/// <summary>
	/// �傫�����擾
	/// </summary>
	/// <returns></returns>
	CVector3 GetScale() {
		return m_scale;
	}

	/// <summary>
	/// ��]��ݒ�
	/// </summary>
	/// <param name="rot">��]</param>
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

	/// <summary>
	/// ���[���h�s���ݒ�
	/// </summary>
	/// <param name="wMat">���[���h�s��</param>
	void SetWorldMatrix(const CMatrix& wMat);

	/// <summary>
	/// ���f�����擾
	/// </summary>
	/// <returns></returns>
	SkinModel& GetModel() {
		return m_skinModel;
	}

	Animation& GetAnim() {
		return m_animation;
	}

    /// <summary>
    /// �V���h�E���󂯂邩�ǂ�����ݒ�
    /// </summary>
    void SetShadowReceive(bool isReceive) {
        m_isShadowReceive = isReceive;
    }

    /// <summary>
    /// �V���h�E���o�����ǂ�����ݒ�
    /// </summary>
    void SetShadowCast(bool isCast);

	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��֐�
	/// </summary>
	void Draw() override;

private:
	SkinModel m_skinModel; //�X�L�����f��

	Animation m_animation; //�A�j���[�V�����𑀍삷��N���X

	CVector3 m_pos = CVector3::Zero();           //�ʒu
	CVector3 m_scale = CVector3::One();          //�傫��
	CQuaternion m_rot = CQuaternion::Identity(); //��]

    bool m_isShadowReceive = false;
    bool m_isShadowCaster = false;
};

