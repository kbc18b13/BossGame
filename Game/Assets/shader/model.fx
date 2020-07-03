/*!
 * @brief	���f���V�F�[�_�[�B
 */
static const int shadowMapNum = 5;

/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//�A���x�h�e�N�X�`���B
Texture2D<float4> albedoTexture : register(t0);	
//�{�[���s��
StructuredBuffer<float4x4> boneMatrix : register(t1);

//�X�y�L�����}�b�v
Texture2D<float> specularMap : register(t2);

//�V���h�E�}�b�v�B
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
// �萔�o�b�t�@�B
/////////////////////////////////////////////////////////////
/*!
 * @brief	���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�B
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
 * @brief	�f�B���N�V�������C�g�̒萔�o�b�t�@�B
 */
cbuffer PSCbDir : register(b1) {
	float4 mLightColor[4];
	float4 mLightVec[4];
};

cbuffer PSCbAmb : register(b2) {
	float4 mAmbColor;
};

//�X�y�L�����p
cbuffer PSEye : register(b3) {
	float3 eyePos;
}

//�V���h�E�}�b�v�p�s��
cbuffer ShadowCamera : register(b4) {
    float4x4 shadowVP[shadowMapNum];
}

cbuffer ShadowCameraFar : register(b5) {
    float4 shadowFar[(shadowMapNum+3)/4];
}

/////////////////////////////////////////////////////////////
//�e��\����
/////////////////////////////////////////////////////////////
/*!
 * @brief	�X�L���Ȃ����f���̒��_�\���́B
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float3 Tangent  : TANGENT;				//�ڃx�N�g���B
    float2 TexCoord : TEXCOORD0;			//UV���W�B
};
/*!
 * @brief	�X�L�����胂�f���̒��_�\���́B
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float2 TexCoord	: TEXCOORD0;			//UV���W�B
    float3 Tangent	: TANGENT;				//�ڃx�N�g���B
    uint4  Indices  : BLENDINDICES0;		//���̒��_�Ɋ֘A�t������Ă���{�[���ԍ��Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
    float4 Weights  : BLENDWEIGHT0;			//���̒��_�Ɋ֘A�t������Ă���{�[���ւ̃X�L���E�F�C�g�Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
};

/*!
 * @brief	�s�N�Z���V�F�[�_�[�̓��́B
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
 *@brief	�X�L���s����v�Z�B
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
 * @brief	�X�L���Ȃ����f���p�̒��_�V�F�[�_�[�B
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	float4 pos = mul(mWorld, In.Position);
    
	psInput.worldPos = pos.xyz;

    //�V���h�E�}�b�vUV
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
 * @brief	�X�L�����胂�f���p�̒��_�V�F�[�_�[�B
 * �S�Ă̒��_�ɑ΂��Ă��̃V�F�[�_�[���Ă΂��B
 * In��1�̒��_�f�[�^�BVSInputNmTxWeights�����Ă݂悤�B
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//��������X�L�j���O���s���Ă���ӏ��B
	//�X�L���s����v�Z�B
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrix�Ƀ{�[���s�񂪐ݒ肳��Ă��āA
			//In.indices�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̔ԍ��B
			//In.weights�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̃E�F�C�g�B
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //�Ō�̃{�[�����v�Z����B
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//���_���W�ɃX�L���s�����Z���āA���_�����[���h��Ԃɕϊ��B
		//mul�͏�Z���߁B
	    pos = mul(skinning, In.Position);
	}
	psInput.Normal = normalize( mul(skinning, float4(In.Normal,0)) ).xyz;
	psInput.Tangent = normalize( mul(skinning, float4(In.Tangent,0)) ).xyz;
	
	psInput.worldPos = pos.xyz;

    //�V���h�E�}�b�vUV
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
// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
    //�A���x�h�e�N�X�`���̓ǂݍ���
	float4 color = albedoTexture.Sample(Sampler, In.TexCoord);
	float4 sum = float4(0, 0, 0, 0);
    
    float shadow = 1;
        
    float z = In.Position.z / In.Position.w;
    if(In.Position.w < shadowFar[0].x){
        //�v���W�F�N�V�����s����o�����W���e�N�X�`�����W�ɕϊ�����B
        float3 shadowPos2 = In.shadowPos[0].xyz / In.shadowPos[0].w;
        shadowPos2.xy *= float2(0.5f, -0.5f);
        shadowPos2.xy += 0.5f;
        //�V���h�E�}�b�v�Ɣ�r���ĉe�̋��������߂�B(0���e�A1���ЂȂ�)�B
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
    
    
    float3 eyeLine = normalize(In.worldPos - eyePos);//�X�y�L�����[�p
	for (int i = 0; i < 4; i++) {
		float3 dir = normalize(mLightVec[i].xyz);
        
		sum += max(dot(In.Normal, -dir), 0) * mLightColor[i] * color * shadow;
		//���ʔ��ˌ�
		if(mHasSpecular){
			float3 refVec = dir + 2 * (In.Normal * dot(In.Normal, -dir));
			float specPower = max(dot(refVec, -eyeLine), 0);
            
            float mapPower = specularMap.Sample(Sampler, In.TexCoord);
			sum += pow(specPower, 10) * (mLightColor[0]*10*mapPower) * shadow;
		}
	}
    //����
	sum += color * mAmbColor*0.5f;
    //�����ɂ��X�y�L�������ˁB
    float mapPower = 0.0f;
    if( mHasSpecular){
        mapPower = specularMap.Sample(Sampler, In.TexCoord);    
    }
   
    	float3 refVec = In.Normal;
		float specPower = max(dot(refVec, -eyeLine), 0);
            
        sum += pow(specPower, 10) * (mAmbColor*mapPower);
    
    //sum *= 0.3f + 0.7f*shadow;
    
    //���Ȕ����F
    sum.xyz += mEmissionColor;
    
	return sum;
}