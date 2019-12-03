#include "stdafx.h"
#include "Bloom.h"


Bloom::Bloom(){}


Bloom::~Bloom(){}

void Bloom::Init(){
    UINT w = FRAME_BUFFER_W;
    UINT h = FRAME_BUFFER_H;

	//�P�x���o�p�^�[�Q�b�g��������
	luminanceTarget.Init( w, h, FRAME_BUFFER_FORMAT );

    //�ŏI�����O�p�^�[�Q�b�g��������
    hurfTarget.Init( w/2, h/2 , FRAME_BUFFER_FORMAT);

    //�_�E���T���v�����O�p�^�[�Q�b�g��������
	ID3D11ShaderResourceView* srv = luminanceTarget.GetRenderTargetSRV();
    for( Blur& bl : downSumples ){
		bl.Init( w, h, FRAME_BUFFER_FORMAT );
		bl.SetSource( srv );
		srv = bl.GetResult();
        w /= 2;
        h /= 2;
    }
}

void Bloom::ApplyEffect( PostEffect& postEffect ){
	using PS = ID3D11PixelShader;
    ID3D11DeviceContext* dc = g_graphicsEngine->GetD3DDeviceContext();

	//�P�x���o
	luminanceTarget.SetToContext( dc );
	postEffect.DrawScreenRect( m_source, (PS*)luminanceShader.GetBody() );

	//�_�E���T���v�����O
	for( int i = 0; i < downSumpleNum; i++){
		downSumples[i].ApplyEffect( postEffect );
		ID3D11ShaderResourceView* srv = downSumples[i].GetResult();
		dc->PSSetShaderResources( i, 1,  &srv);
	}

	//�t���[����2����1�T�C�Y�̃^�[�Q�b�g�Ƀ_�E���T���v�����������̊G�̕��ς��o���B
	hurfTarget.SetToContext( dc );
	postEffect.DrawScreenRect((PS*)luminanceShader.GetBody() );

	//�`�����t���[���o�b�t�@��
	g_graphicsEngine->BegineFrameBuffer();
	postEffect.DrawScreenRect( (PS*)lastShader.GetBody() );
}
