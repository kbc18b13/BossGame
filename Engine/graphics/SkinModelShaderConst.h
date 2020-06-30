/*!
 *@brief	スキンモデル関係関係のシェーダーパラメータ。
 */

#pragma once


/*!
 *@brief	定数バッファのレジスタ番号
 */
enum EnSkinModelCBReg{
	enSkinModelCBReg_VSPS,		//!<頂点シェーダーとピクセルシェーダー共通の定数バッファ。
	enSkinModelCBReg_Light,		//!<ライト用の定数バッファ。
	enSkinModelCBReg_Material,	//!<マテリアルパラメータ。
	enSkinModelCBReg_Specular,  //スペキュラ用
	enSkinModelCBReg_Shadow,	//!<影。
	enSkinModelCBReg_ShadowFar,	//!<影。
	enSkinModelCBReg_GBuffer,	//!<G-Buffer。
	
};
/*!
 *@brief	SRVのレジスタ番号。
 */
enum EnSkinModelSRVReg{
	enSkinModelSRVReg_AlbedoTexture,		//!<アルベドテクスチャ。
	enSkinModelSRVReg_BoneMatrixArray,		//!<ボーン行列の配列。
	enSkinModelSRVReg_Speculer,            //スペキュラマップ
    enSkinModelSRVReg_ShadowMap0,		//!<シャドウマップの配列。
	enSkinModelSRVReg_ShadowMap1,		
	enSkinModelSRVReg_ShadowMap2,		
	enSkinModelSRVReg_ShadowMap3,		
	enSkinModelSRVReg_ShadowMap4,		
};
