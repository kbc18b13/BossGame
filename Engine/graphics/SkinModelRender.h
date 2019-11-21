#pragma once

/// <summary>
/// モデル描画を行うゲームオブジェクト。
/// </summary>
class SkinModelRender : public IGameObject{
public:
	SkinModelRender();
	~SkinModelRender();

	/*!
	*@brief	初期化。
	*@param[in]	filePath		ロードするcmoファイルのファイルパス。
	*@param[in] enFbxUpAxis		fbxの上軸。デフォルトはenFbxUpAxisZ。
	*/
	void Init(const wchar_t* filePath,AnimationClip animClipList[] = nullptr, int numAnimClip = 0,
			  EnFbxUpAxis enFbxUpAxis = enFbxUpAxisY);

	/*!
	*@brief	アニメーションの再生。
	*@param[in]	clipNo	アニメーションクリップの番号。Init関数に渡したanimClipListの並びとなる。
	*@param[in]	interpolateTime		補完時間(単位：秒)
	*/
	void Play(int clipNo, float interpolateTime = 0.0f) {
		m_animation.Play(clipNo, interpolateTime);
	}

	/*!
	* @brief	アニメーションの再生中？
	*/
	bool IsPlaying() const {
		return m_animation.IsPlaying();
	}

	/// <summary>
	/// 位置を設定
	/// </summary>
	/// <param name="pos">位置</param>
	void SetPos(const CVector3& pos) {
		m_pos = pos;
	}

	/// <summary>
	/// 位置を取得
	/// </summary>
	/// <returns></returns>
	CVector3 GetPos() {
		return m_pos;
	}
	
	/// <summary>
	/// 大きさを設定
	/// </summary>
	/// <param name="scale">大きさ</param>
	void SetScale(const CVector3& scale) {
		m_scale = scale;
	}

	/// <summary>
	/// 大きさを取得
	/// </summary>
	/// <returns></returns>
	CVector3 GetScale() {
		return m_scale;
	}

	/// <summary>
	/// 回転を設定
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRot(const CQuaternion& rot) {
		m_rot = rot;
	}

	/// <summary>
	/// 回転を取得
	/// </summary>
	/// <returns></returns>
	CQuaternion GetRot() {
		return m_rot;
	}

	/// <summary>
	/// ワールド行列を設定
	/// </summary>
	/// <param name="wMat">ワールド行列</param>
	void SetWorldMatrix(const CMatrix& wMat);

	/// <summary>
	/// モデルを取得
	/// </summary>
	/// <returns></returns>
	SkinModel& GetModel() {
		return m_skinModel;
	}

	Animation& GetAnim() {
		return m_animation;
	}

    /// <summary>
    /// シャドウを受けるかどうかを設定
    /// </summary>
    void SetShadowReceive(bool isReceive) {
        m_isShadowReceive = isReceive;
    }

    /// <summary>
    /// シャドウを出すかどうかを設定
    /// </summary>
    void SetShadowCast(bool isCast);

	/// <summary>
	/// 更新関数
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw() override;

private:
	SkinModel m_skinModel; //スキンモデル

	Animation m_animation; //アニメーションを操作するクラス

	CVector3 m_pos = CVector3::Zero();           //位置
	CVector3 m_scale = CVector3::One();          //大きさ
	CQuaternion m_rot = CQuaternion::Identity(); //回転

    bool m_isShadowReceive = false;
    bool m_isShadowCaster = false;
};

