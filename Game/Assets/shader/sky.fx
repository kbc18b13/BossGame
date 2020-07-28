/*!
 * @brief	���f���V�F�[�_�[�B
 */

//�A���x�h�e�N�X�`���B
Texture2D<float4> albedoTexture : register(t0);	

//�T���v���X�e�[�g
sampler Sampler : register(s0);

// �萔�o�b�t�@�B
cbuffer VSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
    float3 mEmissionColor;
    float mAlpha;
    int mHasSpecular;
};

//�X�L���Ȃ����f���̒��_�\���́B
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float3 Tangent  : TANGENT;				//�ڃx�N�g���B
    float2 TexCoord : TEXCOORD0;			//UV���W�B
};

//�s�N�Z���V�F�[�_�[�̓��́B
struct PSInput{
	float4 Position 	: SV_POSITION;
	float2 TexCoord 	: TEXCOORD0;
};

/*!--------------------------------------------------------------------------------------
 * @brief	�X�L���Ȃ����f���p�̒��_�V�F�[�_�[�B
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

//�A�����s�N�Z���V�F�[�_�[
float4 PSSky(PSInput In) : SV_Target0{
    float4 color = albedoTexture.Sample(Sampler, In.TexCoord);
    return color;
}