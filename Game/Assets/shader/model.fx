
//�A���x�h�e�N�X�`���B
Texture2D<float4> albedoTexture : register(t0);	

//�X�y�L�����}�b�v
Texture2D<float> specularMap : register(t2);

//�T���v���X�e�[�g
sampler Sampler : register(s0);


//���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�B
cbuffer VSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
    float3 mEmissionColor;
    float mAlpha;
    int mHasSpecular;
};

//�f�B���N�V�������C�g�̒萔�o�b�t�@�B
cbuffer PSCbDir : register(b1) {
	float4 mLightColor[4];
	float4 mLightVec[4];
};

//�A���r�G���g���C�g
cbuffer PSCbAmb : register(b2) {
	float4 mAmbColor;
};

//�X�y�L�����p
cbuffer PSEye : register(b3) {
	float3 eyePos;
}

//�{�[���A�j���[�V�����֘A
#include "inc/Skinning.fxsub"
//�X�L���������f���p
#include "inc/NonSkin.fxsub"
//�J�X�P�[�h�V���h�E�}�b�v�֘A
#include "inc/CascadeShadow.fxsub"

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

/*!--------------------------------------------------------------------------------------
 * @brief	�X�L���Ȃ����f���p�̒��_�V�F�[�_�[�B
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNonSkin In ) 
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


//�X�L�����胂�f���p�̒��_�V�F�[�_�[�B
PSInput VSMainSkin( VSInputSkin In ) 
{
	PSInput psInput = (PSInput)0;

	//�X�L���s����v�Z�B
	float4x4 skinning = CalcSkinMatrix(In);	
	float4 pos = mul(skinning, In.Position);
	psInput.worldPos = pos.xyz;
    
	psInput.Normal = normalize( mul(skinning, float4(In.Normal,0)) ).xyz;
	psInput.Tangent = normalize( mul(skinning, float4(In.Tangent,0)) ).xyz;
	
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


//�s�N�Z���V�F�[�_�[�̃G���g���֐��B
float4 PSMain( PSInput In ) : SV_Target0
{
    //�A���x�h�e�N�X�`���̓ǂݍ���
	float4 albedo = albedoTexture.Sample(Sampler, In.TexCoord);
	float4 sum = float4(0, 0, 0, 0);
    
    //�J�X�P�[�h�V���h�E
    float shadow = CalcShadow(In.shadowPos, In.Position.w);
    
    //�ڐ�
    float3 eyeLine = normalize(In.worldPos - eyePos);
    
    //�f�B���N�V�������C�g
	for (int i = 0; i < 4; i++) {
		float3 dir = normalize(mLightVec[i].xyz);
        
        //�g�U���ˌ�
		sum += max(dot(In.Normal, -dir), 0) * mLightColor[i] * albedo * shadow;
        
		//���ʔ��ˌ�
		if(mHasSpecular){
			float3 refVec = reflect(dir, In.Normal);//���˃x�N�g��
			float specPower = max(dot(refVec, -eyeLine), 0);//�X�y�L�����̋���
            float mapPower = specularMap.Sample(Sampler, In.TexCoord);
            
			sum += pow(specPower, 10) * (mLightColor[0]*10*mapPower) * shadow;
		}
	}
    
    //����
	sum += albedo * mAmbColor;
    
    //�����ɂ��X�y�L�������ˁB
    float mapPower = 0.0f;
    if( mHasSpecular){
        mapPower = specularMap.Sample(Sampler, In.TexCoord);    
    }
    float specPower = max(dot(In.Normal, -eyeLine), 0);
    sum += pow(specPower, 10) * (mAmbColor*mapPower);
    
    //���Ȕ����F
    sum.xyz += mEmissionColor;
    
    //�A���t�@
    sum.w = mAlpha;
    
	return sum;
}