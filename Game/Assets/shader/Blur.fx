/*!
 * @brief	�u���[�V�F�[�_�[�B
 */

 //�e�N�X�`���B
Texture2D<float4> Texture: register( t0 );
// SamplerState
sampler Sampler: register( s0 );

//���_����
struct VSInput
{
	float2 pos: POS;
	float2 uv: UV;
};

//�u���[�̍L��
static const int blurRange = 7;
//�s�N�Z������
struct PSInput
{
	float4 pos: SV_POSITION;
	float2 center: CENTER;
	float2 uv[blurRange]: UV_ARRAY;
};

cbuffer Weight: register( b0 )
{
	float weight[blurRange];
}

PSInput VSBlurX( VSInput input )
{
	PSInput output;
	output.pos = float4( input.pos, 0.5f, 1 );

	float width;
	float height;
    //�P�x�e�N�X�`���̃T�C�Y���擾����B
	Texture.GetDimensions( width, height );
	
	output.center = input.uv;
	
    [unroll]
	for( int i = 0; i < blurRange; i++ )
	{
		output.uv[i] = float2( ( i * 2 + 1 ) / width, 0 );
	}
	return output;
}

PSInput VSBlurY( VSInput input )
{
	PSInput output;
	output.pos = float4( input.pos, 0.5f, 1 );

	float width;
	float height;
    //�P�x�e�N�X�`���̃T�C�Y���擾����B
	Texture.GetDimensions( width, height );

	output.center = input.uv;
	
    [unroll]
	for( int i = 0; i < blurRange; i++ )
	{
		output.uv[i] = float2( 0, ( i * 2 + 1 ) / height );
	}
	return output;
}

float4 PSBlur( PSInput input ): SV_Target
{
	float4 col = float4( 0, 0, 0, 0 );
	
	[unroll]
	for( int i = 0; i < blurRange; i++ )
	{
		col += weight[i] * ( Texture.Sample( Sampler, input.center + input.uv[i] ) +
							 Texture.Sample( Sampler, input.center - input.uv[i] ) );
	}
	
	return col;
}