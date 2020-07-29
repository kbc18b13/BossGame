
//���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�B
cbuffer VSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};


//�X�L���Ȃ����f���p
#include "inc/NonSkin.fxsub"
//�{�[���A�j���[�V�����֌W
#include "inc/Skinning.fxsub"

/*!
 * @brief	�s�N�Z���V�F�[�_�[�̓��́B
 */
struct PSInput{
	float4 Position 	: SV_POSITION;
};


//�X�L���Ȃ����f���p�̒��_�V�F�[�_�[�B
PSInput VSMain( VSInputNonSkin In ) 
{
	PSInput psInput = (PSInput)0;
	float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	return psInput;
}


//�X�L�����胂�f���p�̒��_�V�F�[�_�[�B
PSInput VSMainSkin( VSInputSkin In ) 
{
	PSInput psInput = (PSInput)0;
    
    //�X�L���s����v�Z
	float4x4 skinning = CalcSkinMatrix(In);	
	float4 pos = mul(skinning, In.Position);
	
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
    return psInput;
}

// �s�N�Z���V�F�[�_�[
float4 PSMain( PSInput In ) : SV_Target0
{
    float depth = In.Position.z / In.Position.w;
	return float4(depth,0,0,0);
}