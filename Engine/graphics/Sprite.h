#pragma once
#include "SpriteEffect.h"

class Sprite {
public:
	Sprite();
	~Sprite();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="path">テクスチャパス</param>
	/// <param name="width">幅</param>
	/// <param name="hight">高さ</param>
	void Init(const wchar_t* path, UINT width, UINT height);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/*!
	*@brief	モデルをワールド座標系に変換するためのワールド行列を更新する。
	*@param[in]	position	モデルの座標。
	*@param[in]	rotation	モデルの回転。
	*@param[in]	scale		モデルの拡大率。
	*/
	void UpdateWorldMatrix(const CVector2& pos, const CVector2& scale, const CQuaternion& rot);

	/*!
	*@brief	モデルをワールド座標系に変換するためのワールド行列を更新する。
	*@param[in]	mat        モデルのワールド座標	
	*/
	void UpdateWorldMatrix(const CMatrix& mat) {
		m_worldMat = mat;
	}

private:
	SpriteEffect m_effect;                    //テクスチャやシェーダーなど
	ID3D11Buffer* m_vertex;                   //頂点バッファ
	CMatrix m_worldMat = CMatrix::Identity(); //ワールド行列(CPU)
	ID3D11Buffer* m_worldMatBuf;              //ワールド行列(GPU)
};

