/*!
 * @brief	モデルシェーダー。
 */
static const int shadowMapNum = 5;

/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//アルベドテクスチャ。
Texture2D<float4> albedoTexture : register(t0);	
//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t1);

//スペキュラマップ
Texture2D<float> specularMap : register(t2);

//シャドウマップ。
Texture2D<float4> shadowMap0 : register(t3);
Texture2D<float4> shadowMap1 : register(t4);
Texture2D<float4> shadowMap2 : register(t5);
Texture2D<float4> shadowMap3 : register(t6);
Texture2D<float4> shadowMap4 : register(t7);

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);
SamplerComparisonState compSampler : register(s2);

SamplerState msan
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

/////////////////////////////////////////////////////////////
// 定数バッファ。
/////////////////////////////////////////////////////////////
/*!
 * @brief	頂点シェーダーとピクセルシェーダー用の定数バッファ。
 */
cbuffer VSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
    float3 mEmissionColor;
    float dummy;
    int mHasSpecular;
};

/*!
 * @brief	ディレクションライトの定数バッファ。
 */
cbuffer PSCbDir : register(b1) {
	float4 mLightColor[4];
	float4 mLightVec[4];
};

cbuffer PSCbAmb : register(b2) {
	float4 mAmbColor;
};

//スペキュラ用
cbuffer PSEye : register(b3) {
	float3 eyePos;
}

//シャドウマップ用行列
cbuffer ShadowCamera : register(b4) {
    float4x4 shadowVP[shadowMapNum];
}

cbuffer ShadowCameraFar : register(b5) {
    float4 shadowFar[(shadowMapNum+3)/4];
}

/////////////////////////////////////////////////////////////
//各種構造体
/////////////////////////////////////////////////////////////
/*!
 * @brief	スキンなしモデルの頂点構造体。
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float3 Tangent  : TANGENT;				//接ベクトル。
    float2 TexCoord : TEXCOORD0;			//UV座標。
};
/*!
 * @brief	スキンありモデルの頂点構造体。
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float2 TexCoord	: TEXCOORD0;			//UV座標。
    float3 Tangent	: TANGENT;				//接ベクトル。
    uint4  Indices  : BLENDINDICES0;		//この頂点に関連付けされているボーン番号。x,y,z,wの要素に入っている。4ボーンスキニング。
    float4 Weights  : BLENDWEIGHT0;			//この頂点に関連付けされているボーンへのスキンウェイト。x,y,z,wの要素に入っている。4ボーンスキニング。
};

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
/*!
 *@brief	スキン行列を計算。
 */
float4x4 CalcSkinMatrix(VSInputNmTxWeights In)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
        w += In.Weights[i];
    }
    
    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
    return skinning;
}
/*!--------------------------------------------------------------------------------------
 * @brief	スキンなしモデル用の頂点シェーダー。
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
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

/*!--------------------------------------------------------------------------------------
 * @brief	スキンありモデル用の頂点シェーダー。
 * 全ての頂点に対してこのシェーダーが呼ばれる。
 * Inは1つの頂点データ。VSInputNmTxWeightsを見てみよう。
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//ここからスキニングを行っている箇所。
	//スキン行列を計算。
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //最後のボーンを計算する。
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
	    pos = mul(skinning, In.Position);
	}
	psInput.Normal = normalize( mul(skinning, float4(In.Normal,0)) ).xyz;
	psInput.Tangent = normalize( mul(skinning, float4(In.Tangent,0)) ).xyz;
	
	psInput.worldPos = pos.xyz;

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

//--------------------------------------------------------------------------------------
// ピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
    //アルベドテクスチャの読み込み
	float4 color = albedoTexture.Sample(Sampler, In.TexCoord);
	float4 sum = float4(0, 0, 0, 0);
    
    float shadow = 1;
        
    float z = In.Position.z / In.Position.w;
    if(In.Position.w < shadowFar[0].x){
        //プロジェクション行列を経た座標をテクスチャ座標に変換する。
        float3 shadowPos2 = In.shadowPos[0].xyz / In.shadowPos[0].w;
        shadowPos2.xy *= float2(0.5f, -0.5f);
        shadowPos2.xy += 0.5f;
        //シャドウマップと比較して影の強さを決める。(0が影、1がひなた)。
        shadow = shadowMap0.SampleCmp(compSampler, shadowPos2.xy, shadowPos2.z - 0.003f);
            
    }else if(In.Position.w < shadowFar[0].y){
        float3 shadowPos2 = In.shadowPos[1].xyz / In.shadowPos[1].w;
        shadowPos2.xy *= float2(0.5f, -0.5f);
        shadowPos2.xy += 0.5f;
        shadow = shadowMap1.SampleCmp(compSampler, shadowPos2.xy, shadowPos2.z - 0.003f);
            
    }else if(In.Position.w < shadowFar[0].z){
        float3 shadowPos2 = In.shadowPos[2].xyz / In.shadowPos[2].w;
        shadowPos2.xy *= float2(0.5f, -0.5f);
        shadowPos2.xy += 0.5f;
        shadow = shadowMap2.SampleCmp(compSampler, shadowPos2.xy, shadowPos2.z - 0.003f);
            
    }else if(In.Position.w < shadowFar[0].w){
        float3 shadowPos2 = In.shadowPos[3].xyz / In.shadowPos[3].w;
        shadowPos2.xy *= float2(0.5f, -0.5f);
        shadowPos2.xy += 0.5f;
        shadow = shadowMap3.SampleCmp(compSampler, shadowPos2.xy, shadowPos2.z - 0.003f);
            
    }else if(In.Position.w < shadowFar[1].x){
        float3 shadowPos2 = In.shadowPos[4].xyz / In.shadowPos[4].w;
        shadowPos2.xy *= float2(0.5f, -0.5f);
        shadowPos2.xy += 0.5f;
        shadow = shadowMap4.SampleCmp(compSampler, shadowPos2.xy, shadowPos2.z - 0.001f);
    }
    
    
    float3 eyeLine = normalize(In.worldPos - eyePos);//スペキュラー用
	for (int i = 0; i < 4; i++) {
		float3 dir = normalize(mLightVec[i].xyz);
        
		sum += max(dot(In.Normal, -dir), 0) * mLightColor[i] * color * shadow;
		//鏡面反射光
		if(mHasSpecular){
			float3 refVec = dir + 2 * (In.Normal * dot(In.Normal, -dir));
			float specPower = max(dot(refVec, -eyeLine), 0);
            
            float mapPower = specularMap.Sample(Sampler, In.TexCoord);
			sum += pow(specPower, 10) * (mLightColor[0]*10*mapPower) * shadow;
		}
	}
    //環境光
	sum += color * mAmbColor*0.5f;
    //環境光によるスペキュラ反射。
    float mapPower = 0.0f;
    if( mHasSpecular){
        mapPower = specularMap.Sample(Sampler, In.TexCoord);    
    }
   
    	float3 refVec = In.Normal;
		float specPower = max(dot(refVec, -eyeLine), 0);
            
        sum += pow(specPower, 10) * (mAmbColor*mapPower);
    
    //sum *= 0.3f + 0.7f*shadow;
    
    //自己発光色
    sum.xyz += mEmissionColor;
    
	return sum;
}