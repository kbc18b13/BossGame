
//頂点シェーダーとピクセルシェーダー用の定数バッファ。
cbuffer VSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};


//スキンなしモデル用
#include "inc/NonSkin.fxsub"
//ボーンアニメーション関係
#include "inc/Skinning.fxsub"

/*!
 * @brief	ピクセルシェーダーの入力。
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
};


//スキンなしモデル用の頂点シェーダー。
PSInput VSMain( VSInputNonSkin In ) 
{
	PSInput psInput = (PSInput)0;
	float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}


//スキンありモデル用の頂点シェーダー。
PSInput VSMainSkin( VSInputSkin In ) 
{
	PSInput psInput = (PSInput)0;
    
    //スキン行列を計算
	float4x4 skinning = CalcSkinMatrix(In);	
	float4 pos = mul(skinning, In.Position);
	
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
    return psInput;
}

// ピクセルシェーダー
float4 PSMain( PSInput In ) : SV_Target0
{
    float depth = In.Position.z / In.Position.w;
	return float4(depth,0,0,0);
}