
//アルベドテクスチャ。
Texture2D<float4> albedoTexture : register(t0);	

//スペキュラマップ
Texture2D<float> specularMap : register(t2);

//サンプラステート
sampler Sampler : register(s0);


//頂点シェーダーとピクセルシェーダー用の定数バッファ。
cbuffer VSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
    float3 mEmissionColor;
    float mAlpha;
    int mHasSpecular;
};

//ディレクションライトの定数バッファ。
cbuffer PSCbDir : register(b1) {
	float4 mLightColor[4];
	float4 mLightVec[4];
};

//アンビエントライト
cbuffer PSCbAmb : register(b2) {
	float4 mAmbColor;
};

//スペキュラ用
cbuffer PSEye : register(b3) {
	float3 eyePos;
}

//ボーンアニメーション関連
#include "inc/Skinning.fxsub"
//スキン無しモデル用
#include "inc/NonSkin.fxsub"
//カスケードシャドウマップ関連
#include "inc/CascadeShadow.fxsub"

/*!
 * @brief	ピクセルシェーダーの入力。
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord 	: TEXCOORD0;
	float3 worldPos     : WORLD;
    float4 shadowPos[shadowMapNum]     : SHADOW;
};

/*!--------------------------------------------------------------------------------------
 * @brief	スキンなしモデル用の頂点シェーダー。
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNonSkin In ) 
{
	PSInput psInput = (PSInput)0;
	float4 pos = mul(mWorld, In.Position);
    
	psInput.worldPos = pos.xyz;

    //シャドウマップUV
    for(int i = 0; i < shadowMapNum; i++){
        psInput.shadowPos[i] = mul(shadowVP[i], pos);
    }

	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	psInput.Normal = normalize(mul(mWorld, float4(In.Normal,0))).xyz;
	psInput.Tangent = normalize(mul(mWorld, float4(In.Tangent,0))).xyz;
	return psInput;
}


//スキンありモデル用の頂点シェーダー。
PSInput VSMainSkin( VSInputSkin In ) 
{
	PSInput psInput = (PSInput)0;

	//スキン行列を計算。
	float4x4 skinning = CalcSkinMatrix(In);	
	float4 pos = mul(skinning, In.Position);
	psInput.worldPos = pos.xyz;
    
	psInput.Normal = normalize( mul(skinning, float4(In.Normal,0)) ).xyz;
	psInput.Tangent = normalize( mul(skinning, float4(In.Tangent,0)) ).xyz;
	
    //シャドウマップUV
    for(int i = 0; i < shadowMapNum; i++){
        psInput.shadowPos[i] = mul(shadowVP[i], pos);
    }
    
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
    return psInput;
}


//ピクセルシェーダーのエントリ関数。
float4 PSMain( PSInput In ) : SV_Target0
{
    //アルベドテクスチャの読み込み
	float4 albedo = albedoTexture.Sample(Sampler, In.TexCoord);
	float4 sum = float4(0, 0, 0, 0);
    
    //カスケードシャドウ
    float shadow = CalcShadow(In.shadowPos, In.Position.w);
    
    //目線
    float3 eyeLine = normalize(In.worldPos - eyePos);
    
    //ディレクションライト
	for (int i = 0; i < 4; i++) {
		float3 dir = normalize(mLightVec[i].xyz);
        
        //拡散反射光
		sum += max(dot(In.Normal, -dir), 0) * mLightColor[i] * albedo * shadow;
        
		//鏡面反射光
		if(mHasSpecular){
			float3 refVec = reflect(dir, In.Normal);//反射ベクトル
			float specPower = max(dot(refVec, -eyeLine), 0);//スペキュラの強さ
            float mapPower = specularMap.Sample(Sampler, In.TexCoord);
            
			sum += pow(specPower, 10) * (mLightColor[0]*10*mapPower) * shadow;
		}
	}
    
    //環境光
	sum += albedo * mAmbColor;
    
    //環境光によるスペキュラ反射。
    float mapPower = 0.0f;
    if( mHasSpecular){
        mapPower = specularMap.Sample(Sampler, In.TexCoord);    
    }
    float specPower = max(dot(In.Normal, -eyeLine), 0);
    sum += pow(specPower, 10) * (mAmbColor*mapPower);
    
    //自己発光色
    sum.xyz += mEmissionColor;
    
    //アルファ
    sum.w = mAlpha;
    
	return sum;
}