/*!
 * @brief	モデルシェーダー。
 */

//アルベドテクスチャ。
Texture2D<float4> albedoTexture : register(t0);	

//サンプラステート
sampler Sampler : register(s0);

// 定数バッファ。
cbuffer VSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
    float3 mEmissionColor;
    float mAlpha;
    int mHasSpecular;
};

//スキンなしモデルの頂点構造体。
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float3 Tangent  : TANGENT;				//接ベクトル。
    float2 TexCoord : TEXCOORD0;			//UV座標。
};

//ピクセルシェーダーの入力。
struct PSInput{
	float4 Position 	: SV_POSITION;
	float2 TexCoord 	: TEXCOORD0;
};

/*!--------------------------------------------------------------------------------------
 * @brief	スキンなしモデル用の頂点シェーダー。
-------------------------------------------------------------------------------------- */
PSInput VSSky( VSInputNmTxVcTangent In ) 
{
	PSInput psInput;
    
	float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	return psInput;
}

//陰無しピクセルシェーダー
float4 PSSky(PSInput In) : SV_Target0{
    float4 color = albedoTexture.Sample(Sampler, In.TexCoord);
    return color;
}